#include "draw.h"
#include "sdl.h"

int main() {
	init_sdl(":3", 1280, 960);
	init_ogl(1280, 960);
	while (1) {
		if (poll_sdl() != 0) break;
		poll_ogl();
    	SDL_GL_SwapWindow(g_sdlwindow);
	}
	deinit_sdl();
	return 0;
}
