#include "shader.h"
#include "glad/glad.h"
#include <stdio.h>
#include <stdlib.h>

uint32_t new_shader(const char* src, int type) {
    unsigned int shader_tag;
    shader_tag = glCreateShader(type);
    glShaderSource(shader_tag, 1, &src, NULL);
    glCompileShader(shader_tag);

    int  success;
    char infoLog[512];
    glGetShaderiv(shader_tag, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader_tag, 512, NULL, infoLog);
        dprintf(2, "oh no! a %s shader failed to compile! aborting...\n", type == GL_VERTEX_SHADER ? "vertex" : "fragment");
        dprintf(2, "more info: %s\n", infoLog);
        exit(success);
    }

    return shader_tag;
}

uint32_t new_program(uint32_t vtx_tag, uint32_t frag_tag) {
    uint32_t program_tag = glCreateProgram();
    glAttachShader(program_tag, vtx_tag);
    glAttachShader(program_tag, frag_tag);
    glLinkProgram(program_tag);

    int  success;
    char infoLog[512];
    glGetProgramiv(program_tag, GL_COMPILE_STATUS, &success);
    if (success == 0) {
        glGetProgramInfoLog(program_tag, 512, NULL, infoLog);
        dprintf(2, "oh no! a shader program failed to link! aborting...\n");
        dprintf(2, "more info: %s\n", infoLog);
        exit(success);
    }

    glDeleteShader(vtx_tag);
    glDeleteShader(frag_tag);

    return program_tag;
}

void activate_program(uint32_t program_tag) {
    glUseProgram(program_tag);
}
