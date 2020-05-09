// Copyright (C) 2000-2013 SuperWaba Ltda.
//
// TotalCross Software Development Kit
//
// This library and virtual machine is distributed in the hope that it will
// be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//
// SPDX-License-Identifier: LGPL-2.1-only

#define BITS_PER_PIXEL 16
#define PIXEL_NATIVE_FORMAT 1
#define DISPLAY_INDEX 0
#define NO_FLAGS 0
#define PITCH_MULTIPLIER 4

#include "tcvm.h"
#include "tcsdl.h"
#include "SkImage.h"

SDL_Window *window;
SDL_Surface *sdlsurface;

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
  // Adjusts screen's BPP
  screen->bpp = BITS_PER_PIXEL;
  // Adjusts screen's pixel format
  screen->pixels = (uint8*)PIXEL_NATIVE_FORMAT;

  // Create a 2D rendering context for a window.
  renderer = SDL_CreateRenderer(window, -1, NO_FLAGS);
  if(renderer == NULL) {
    printf("SDL_CreateRenderer failed: %s\n", SDL_GetError());
  }

  // Print renderer driver information
  SDL_RendererInfo rendererInfo;
  SDL_GetRendererInfo(renderer, &rendererInfo);
  printf("Renderer info: %s\n", rendererInfo.name);

  // Set render driver 
  SDL_SetHint(SDL_HINT_RENDER_DRIVER, rendererInfo.name);

  // Get the SDL surface associated with the window.
  sdlsurface = SDL_GetWindowSurface(window);
  if(sdlsurface == NULL) {
    printf("SDL_GetWindowSurface failed: %s\n", SDL_GetError());
  }

  // Create a texture from an existing sdlsurface.
  texture = SDL_CreateTextureFromSurface(renderer, sdlsurface);
  if(texture == NULL) {
    printf("SDL_CreateTextureFromSurface: %s\n", SDL_GetError());
  }
  return 1;
}

void updateSDLScreen(int w, int h, void *pixels) {
  // Set a texture as the current rendering target.
  SDL_SetRenderTarget(renderer, texture);
  // Update the given texture rectangle with new pixel data.
  SDL_UpdateTexture(texture, NULL, pixels, w * PITCH_MULTIPLIER);
  // Call SDL render present 
  sdlPresent();
}

bool sdlPresent() {
  if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout)) {
    // This function clears the entire rendering target, ignoring the viewport and
    // the clip rectangle.
    SDL_RenderClear(renderer);
    // Copy a portion of the texture to the current rendering target.
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    // Update the screen with rendering performed.
    SDL_RenderPresent(renderer);
    return 0;
  }
  return 1;
}

int ColorFormatSDL2Skia (int pixelFormat) {
  switch (pixelFormat)
  { 
    case SDL_PIXELFORMAT_UNKNOWN    	: return	kUnknown_SkColorType;
    case SDL_PIXELFORMAT_INDEX1LSB	  : return	kUnknown_SkColorType;
    case SDL_PIXELFORMAT_INDEX1MSB		: return  kUnknown_SkColorType;
    case SDL_PIXELFORMAT_INDEX4LSB		: return  kUnknown_SkColorType;
    case SDL_PIXELFORMAT_INDEX4MSB	  : return	kUnknown_SkColorType;
    case SDL_PIXELFORMAT_INDEX8		    : return  kUnknown_SkColorType;
    case SDL_PIXELFORMAT_RGB332		    : return  kUnknown_SkColorType;
    case SDL_PIXELFORMAT_RGB444		    : return  kUnknown_SkColorType;
    case SDL_PIXELFORMAT_RGB555		    : return  kUnknown_SkColorType;
    case SDL_PIXELFORMAT_BGR555	      : return	kUnknown_SkColorType;
    case SDL_PIXELFORMAT_ARGB4444	    : return 	kARGB_4444_SkColorType;
    case SDL_PIXELFORMAT_RGBA4444	    : return	kUnknown_SkColorType;
    case SDL_PIXELFORMAT_ABGR4444		  : return  kUnknown_SkColorType;
    case SDL_PIXELFORMAT_BGRA4444	    : return	kUnknown_SkColorType;
    case SDL_PIXELFORMAT_ARGB1555	    : return	kUnknown_SkColorType;
    case SDL_PIXELFORMAT_RGBA5551	    : return	kRGBA_8888_SkColorType;
    case SDL_PIXELFORMAT_ABGR1555	    : return	kUnknown_SkColorType;
    case SDL_PIXELFORMAT_BGRA5551	    : return	kUnknown_SkColorType;
    case SDL_PIXELFORMAT_RGB565		    : return  kRGB_565_SkColorType;
    case SDL_PIXELFORMAT_BGR565	      : return	kUnknown_SkColorType;
    case SDL_PIXELFORMAT_RGB24		    : return  kUnknown_SkColorType;
    case SDL_PIXELFORMAT_BGR24	      : return	kUnknown_SkColorType;
    case SDL_PIXELFORMAT_RGB888	      : return	kBGRA_8888_SkColorType;
    case SDL_PIXELFORMAT_RGBX8888   	: return	kRGBA_8888_SkColorType;
    case SDL_PIXELFORMAT_BGR888	      : return	kBGRA_8888_SkColorType;
    case SDL_PIXELFORMAT_BGRX8888	    : return 	kBGRA_8888_SkColorType;
    case SDL_PIXELFORMAT_ARGB8888	    : return	kUnknown_SkColorType;
    case SDL_PIXELFORMAT_RGBA8888		  : return  kRGBA_8888_SkColorType;
    case SDL_PIXELFORMAT_ABGR8888		  : return  kUnknown_SkColorType;
    case SDL_PIXELFORMAT_BGRA8888	    : return	kBGRA_8888_SkColorType;
    case SDL_PIXELFORMAT_ARGB2101010	: return	kUnknown_SkColorType;
    case SDL_PIXELFORMAT_YV12		      : return  kUnknown_SkColorType;
    case SDL_PIXELFORMAT_IYUV		      : return  kUnknown_SkColorType;
    case SDL_PIXELFORMAT_YUY2		      : return  kUnknown_SkColorType;
    case SDL_PIXELFORMAT_UYVY		      : return  kUnknown_SkColorType;
    case SDL_PIXELFORMAT_YVYU		      : return  kUnknown_SkColorType;
    default                           : return  kUnknown_SkColorType;
  }
}
