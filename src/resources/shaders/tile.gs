#version 330 core
layout (points) in;
layout (triangle_strip, max_vertices = 8) out;

uniform mat4 view;
uniform vec3 border_color;

float rad = 25;
float border = 2;

in VS_OUT {
    uint state;
    uint value;
} gs_in[];

out GS_OUT {
    vec2 tex_coord;
    vec3 color;
    bool has_tex;
} gs_out;

void gen_outer(vec4 _pos)
{
    gl_Position = view * (_pos + vec4(rad, rad, 0, 0));
    gs_out.tex_coord = vec2(0, 0); gs_out.has_tex = false;
    gs_out.color = border_color;
    EmitVertex();

    gl_Position = view * (_pos + vec4(rad, -1 * rad, 0, 0));
    gs_out.tex_coord = vec2(0, 0); gs_out.has_tex = false;
    gs_out.color = border_color;
    EmitVertex();
    
    gl_Position = view * (_pos + vec4(-1 * rad, rad, 0, 0));
    gs_out.tex_coord = vec2(0, 0); gs_out.has_tex = false;
    gs_out.color = border_color;
    EmitVertex();

    gl_Position = view * (_pos + vec4(-1 * rad, -1 * rad, 0, 0));
    gs_out.tex_coord = vec2(0, 0); gs_out.has_tex = false;
    gs_out.color = border_color;
    EmitVertex();
    EndPrimitive();

}

vec2 gen_tex_coords(uint _state, uint _value, int _pos)
{
    return vec2(0, 0);
}

void gen_inner(vec4 _pos, uint _state, uint _value)
{
    float new_rad = rad - border;

    gl_Position = view * (_pos + vec4(new_rad, new_rad, 0.01f, 0));
    gs_out.tex_coord = vec2(0, 0); gs_out.has_tex = false;
    gs_out.color = vec3(0.0f, 0.0f, 0.0f);
    EmitVertex();

    gl_Position = view * (_pos + vec4(new_rad, -1 * new_rad, 0.01f, 0));
    gs_out.tex_coord = vec2(0, 0); gs_out.has_tex = false;
    gs_out.color = vec3(0.0f, 0.0f, 0.0f);
    EmitVertex();
    
    gl_Position = view * (_pos + vec4(-1 * new_rad, new_rad, 0.01f, 0));
    gs_out.tex_coord = vec2(0, 0); gs_out.has_tex = false;
    gs_out.color = vec3(0.0f, 0.0f, 0.0f);
    EmitVertex();

    gl_Position = view * (_pos + vec4(-1 * new_rad, -1 * new_rad, 0.01f, 0));
    gs_out.tex_coord = vec2(0, 0); gs_out.has_tex = false;
    gs_out.color = vec3(0.0f, 0.0f, 0.0f);
    EmitVertex();
    EndPrimitive();
}
void main() {    
    gen_outer(gl_in[0].gl_Position);
    gen_inner(gl_in[0].gl_Position, gs_in[0].state, gs_in[0].value);
}  