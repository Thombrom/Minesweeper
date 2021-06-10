#version 330 core
layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec3 a_col;

out vec3 color;

uniform mat4 transform;
uniform mat4 view;

void main()
{
    gl_Position = view * transform * vec4(a_pos, 1.0f);
    color = a_col;
}