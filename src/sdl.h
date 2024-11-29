#pragma once
#include <SDL2/SDL.h>

extern SDL_Window* g_sdlwindow;
extern SDL_GLContext g_context;

void init_sdl(const char* title, int w, int h);

int poll_sdl();

void deinit_sdl();
