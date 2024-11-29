#include "draw.h"
#include <assert.h>
#include "tex.h"
#include "vmem.h"
#include "glad/glad.h"
#include "shader.h"
#include <SDL2/SDL_stdinc.h>
#include <string.h>

float vtxes[20] = {
    -0.66, 0.66, 0, 0,1,
    -0.66, -0.66, 0, 0,0,
    0.66, 0.66, 0, 1,1,
    0.66, -0.66, 0, 1,0
    };
uint32_t program_tag, texture_tag, array_tag;

uint8_t tex[192] = { 0 };

static void gen_checkerboard() {
    for (int i = 0; i < 192; i += 3) {
        tex[i  ] = i & 1 ? 0xFF : 0;
        tex[i+1] = i & 1 ? 0xFF : 0;
        tex[i+2] = i & 1 ? 0xFF : 0;
    }
}

void init_ogl(int w, int h) {
    glViewport(0, 0, w, h);

    glEnable(GL_DEPTH_TEST);

    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);

    gen_checkerboard();

    char* vtx_shader_mem;
    char* frag_shader_mem;
    
    {
        FILE* vtx_shader_fi = fopen("glsl/passthru.vs", "r");
        assert(vtx_shader_fi);
        fseek(vtx_shader_fi, 0, SEEK_END);
        int vend = ftell(vtx_shader_fi);
        fseek(vtx_shader_fi, 0, SEEK_SET);
        vtx_shader_mem = malloc(vend + 1);
        memset(vtx_shader_mem, 0, vend + 1);
        fread(vtx_shader_mem, vend, 1, vtx_shader_fi);
        fclose(vtx_shader_fi);
    }

    {
        FILE* frag_shader_fi = fopen("glsl/passthru.fs", "r");
        assert(frag_shader_fi);
        fseek(frag_shader_fi, 0, SEEK_END);
        int fend = ftell(frag_shader_fi);
        fseek(frag_shader_fi, 0, SEEK_SET);
        frag_shader_mem = malloc(fend + 1);
        memset(frag_shader_mem, 0, fend + 1);
        fread(frag_shader_mem, fend, 1, frag_shader_fi);
        fclose(frag_shader_fi);
    }

    uint32_t vtx_tag = new_shader(vtx_shader_mem, GL_VERTEX_SHADER);
    uint32_t frag_tag = new_shader(frag_shader_mem, GL_FRAGMENT_SHADER);
    program_tag = new_program(vtx_tag, frag_tag);
    activate_program(program_tag);

    texture_tag = new_texture(4, 4, GL_RGB, GL_UNSIGNED_BYTE, tex);

    array_tag = new_array(vtxes, sizeof(vtxes), GL_STATIC_DRAW);
}

void poll_ogl() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    activate_program(program_tag);
    activate_texture(texture_tag);
    activate_array(array_tag);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}
