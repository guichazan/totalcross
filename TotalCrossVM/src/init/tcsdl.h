// Copyright (C) 2000-2013 SuperWaba Ltda.
//
// TotalCross Software Development Kit
//
// This library and virtual machine is distributed in the hope that it will
// be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//
// SPDX-License-Identifier: LGPL-2.1-only

#ifndef TCSDL_H
#define TCSDL_H

#ifdef __cplusplus
extern "C" {
#endif

    #include "SDL2/SDL.h"
    #include "GraphicsPrimitives.h"

    extern SDL_Window *window;
    extern SDL_Surface *sdlsurface;

    int initSDL(ScreenSurface screen);
    void updateSDLScreen(int w, int h, void *pixels);
    bool sdlPresent();
    int ColorFormatSDL2Skia (int pixelFormat);

#ifdef __cplusplus
}
#endif

#endif
