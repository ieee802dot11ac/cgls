#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 vert_st;

out vec2 st;

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    st = vert_st;
}