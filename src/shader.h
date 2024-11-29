#pragma once
#include <SDL2/SDL_stdinc.h>

uint32_t new_shader(const char* src, int type);

uint32_t new_program(uint32_t vtx_tag, uint32_t frag_tag);

void activate_program(uint32_t program_tag);
