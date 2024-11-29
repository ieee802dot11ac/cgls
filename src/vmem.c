#include "vmem.h"
#include "glad/glad.h"

uint32_t new_array(void* buf, uint32_t bufsiz, int draw_variant) {
    uint32_t buf_tag, array_tag;
    glGenBuffers(1, &buf_tag);
    glGenVertexArrays(1, &array_tag);
    glBindVertexArray(array_tag);

    glBindBuffer(GL_ARRAY_BUFFER, buf_tag);

    glBufferData(GL_ARRAY_BUFFER, bufsiz, buf, draw_variant);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    return array_tag;
}

void activate_array(uint32_t array_tag) {
    glBindBuffer(GL_ARRAY_BUFFER, array_tag);
}
