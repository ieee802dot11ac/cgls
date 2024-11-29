#include "tex.h"

uint32_t new_texture(int w, int h, GLenum format, GLenum datasize, const void* data) {
    return new_texture_ext(w, h, format, format, datasize, data);
}

uint32_t new_texture_ext(int w, int h, GLenum internal_fmt, GLenum format, GLenum datasize, const void* data) {
    uint32_t texture_tag;

    glGenTextures(1 ,&texture_tag);
    glBindTexture(GL_TEXTURE_2D, texture_tag);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, internal_fmt, w, h, 0, format, datasize, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    return texture_tag;
}

void activate_texture(uint32_t texture_tag) {
    glBindTexture(GL_TEXTURE_2D, texture_tag);
}
