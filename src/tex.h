#pragma once
#include "glad/glad.h"
#include <SDL2/SDL_stdinc.h>

uint32_t new_texture(int w, int h, GLenum format, GLenum datasize, const void* data);

uint32_t new_texture_ext(int w, int h, GLenum internal_fmt, GLenum format, GLenum datasize, const void* data);

void activate_texture(uint32_t texture_tag);
