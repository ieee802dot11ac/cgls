#include "sdl.h"
#include "glad/glad.h"
#include <SDL2/SDL.h>
#include <assert.h>

SDL_Window* g_sdlwindow;
SDL_GLContext g_context;

void init_sdl(const char* title, int w, int h) {
    g_sdlwindow = SDL_CreateWindow(
        title, 
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, 
        w == 0 ? 1280 : w, 
        h == 0 ? 960 : h, 
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    g_context = SDL_GL_CreateContext(g_sdlwindow);
    assert(gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress));
}

int poll_sdl() {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT:
            return -1;
    }
    return 0;
}

void deinit_sdl() {
    SDL_GL_DeleteContext(g_context);
    SDL_DestroyWindow(g_sdlwindow);
    g_sdlwindow = NULL;
}
