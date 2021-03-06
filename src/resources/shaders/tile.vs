#version 330 core
layout (location = 0) in vec3 a_pos;
layout (location = 1) in float a_state;
layout (location = 2) in float a_value;

uniform mat4 view;

out VS_OUT {
    float state;
    float value;
} vs_out;

void main()
{
    gl_Position  = vec4(a_pos, 1.0f);
    vs_out.state = a_state;
    vs_out.value = a_value;
}
