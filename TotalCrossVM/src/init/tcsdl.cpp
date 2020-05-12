// Copyright (C) 2000-2013 SuperWaba Ltda.
//
// TotalCross Software Development Kit
//
// This library and virtual machine is distributed in the hope that it will
// be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//
// SPDX-License-Identifier: LGPL-2.1-only

#define PIXEL_NATIVE_FORMAT 1
#define DISPLAY_INDEX 0
#define NO_FLAGS 0
#define PITCH_MULTIPLIER 4
#define TICKS_FOR_NEXT_FRAME 22

#include "tcsdl.h"

SDL_Window *window;
SDL_Surface *surfaceSDL;
SDL_RendererInfo rendererInfo;

static SDL_Renderer *renderer;
static SDL_Texture *texture;

Uint32 timeout;

int initSDL(ScreenSurface screen) {
  // Only init video (without audio)
  if(SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL_Init failed: %s\n", SDL_GetError()); 
  }

  // Get the desktop area represented by a display, with the primary
  // display located at 0,0 based on rect allocated on initial position
  SDL_Rect rect;
  if(SDL_GetDisplayBounds(DISPLAY_INDEX, &rect) < 0 ) {
    printf("SDL_GetDisplayBounds failed: %s\n", SDL_GetError());
  }

  // Create the window
  window = SDL_CreateWindow("TotalCross SDK", 
                            SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED, 
                            rect.w, 
                            rect.h, 
                            SDL_WINDOW_FULLSCREEN);
  if(window == NULL) {
    printf("SDL_CreateWindow failed: %s\n", SDL_GetError());
  }

  // Get the size of a window's client area.
  SDL_GetWindowSize(window, &screen->screenW, &screen->screenH);

  // Create a 2D rendering context for a window.
  renderer = SDL_CreateRenderer(window, -1, NO_FLAGS);
  if(renderer == NULL) {
    printf("SDL_CreateRenderer failed: %s\n", SDL_GetError());
  }

  // Print renderer driver information
  SDL_GetRendererInfo(renderer, &rendererInfo);
  printf("Renderer info: %s\n", rendererInfo.name);

  // Set render driver 
  SDL_SetHint(SDL_HINT_RENDER_DRIVER, rendererInfo.name);

  // Get the SDL surface associated with the window.
  surfaceSDL = SDL_GetWindowSurface(window);
  if(surfaceSDL == NULL) {
    printf("SDL_GetWindowSurface failed: %s\n", SDL_GetError());
  }

  // Adjusts screen's BPP
  screen->bpp = surfaceSDL->format->BitsPerPixel;
  // Adjusts screen's pixel format
  screen->pixels = (uint8*)PIXEL_NATIVE_FORMAT;

  // Create a texture from an existing surfaceSDL.
  texture = SDL_CreateTextureFromSurface(renderer, surfaceSDL);
  if(texture == NULL) {
    printf("SDL_CreateTextureFromSurface: %s\n", SDL_GetError());
  }
  return 1;
}

void updateScreenSDL(int w, int h, void *pixels) {
  if (strEq(rendererInfo.name,"software")) {
    SDL_UpdateWindowSurface(window);
  }
  else {
    // Set a texture as the current rendering target.
    SDL_SetRenderTarget(renderer, texture);
    // Update the given texture rectangle with new pixel data.
    SDL_UpdateTexture(texture, NULL, pixels, w * PITCH_MULTIPLIER);
  }

  // Call SDL render present 
  presentSDL();
}

void presentSDL() {
  if (strEq(rendererInfo.name,"software")) {
    printf("Renderer info: software present\n");
    if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout)) {
      // SDL_RenderPresent(renderer);
      SDL_UpdateWindowSurface(window);
      timeout = SDL_GetTicks() + TICKS_FOR_NEXT_FRAME;
    }
  }
  else {
    printf("Renderer info: %s present", rendererInfo.name);
    // This function clears the entire rendering target, ignoring the viewport and
    // the clip rectangle.
    SDL_RenderClear(renderer);
    // Copy a portion of the texture to the current rendering target.
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    // Update the screen with rendering performed.
    SDL_RenderPresent(renderer);
  }
}
int pixelFormatSDL (int pixelFormat) {
  switch (pixelFormat) { 
    case SDL_PIXELFORMAT_UNKNOWN    	: return  0;
    case SDL_PIXELFORMAT_INDEX1LSB	  : return  1;
    case SDL_PIXELFORMAT_INDEX1MSB		: return  2;
    case SDL_PIXELFORMAT_INDEX4LSB		: return  3;
    case SDL_PIXELFORMAT_INDEX4MSB	  : return  4;
    case SDL_PIXELFORMAT_INDEX8		    : return  5;
    case SDL_PIXELFORMAT_RGB332		    : return  6;
    case SDL_PIXELFORMAT_RGB444		    : return  7;
    case SDL_PIXELFORMAT_RGB555		    : return  8;
    case SDL_PIXELFORMAT_BGR555	      : return  9;
    case SDL_PIXELFORMAT_ARGB4444	    : return 10;
    case SDL_PIXELFORMAT_RGBA4444	    : return 11;
    case SDL_PIXELFORMAT_ABGR4444		  : return 12;
    case SDL_PIXELFORMAT_BGRA4444	    : return 13;
    case SDL_PIXELFORMAT_ARGB1555	    : return 14;
    case SDL_PIXELFORMAT_RGBA5551	    : return 15;
    case SDL_PIXELFORMAT_ABGR1555	    : return 16;
    case SDL_PIXELFORMAT_BGRA5551	    : return 17;
    case SDL_PIXELFORMAT_RGB565		    : return 18;
    case SDL_PIXELFORMAT_BGR565	      : return 19;
    case SDL_PIXELFORMAT_RGB24		    : return 20;
    case SDL_PIXELFORMAT_BGR24	      : return 21;
    case SDL_PIXELFORMAT_RGB888	      : return 22;
    case SDL_PIXELFORMAT_RGBX8888   	: return 23;
    case SDL_PIXELFORMAT_BGR888	      : return 24;
    case SDL_PIXELFORMAT_BGRX8888	    : return 25;
    case SDL_PIXELFORMAT_ARGB8888	    : return 26;
    case SDL_PIXELFORMAT_RGBA8888		  : return 27;
    case SDL_PIXELFORMAT_ABGR8888		  : return 28;
    case SDL_PIXELFORMAT_BGRA8888	    : return 29;
    case SDL_PIXELFORMAT_ARGB2101010	: return 30;
    case SDL_PIXELFORMAT_YV12		      : return 31;
    case SDL_PIXELFORMAT_IYUV		      : return 32;
    case SDL_PIXELFORMAT_YUY2		      : return 33;
    case SDL_PIXELFORMAT_UYVY		      : return 34;
    case SDL_PIXELFORMAT_YVYU		      : return 35;
  }
}