#version 330 core
layout (points) in;
layout (triangle_strip, max_vertices = 8) out;

uniform mat4 view;
uniform vec3 border_color;

float rad = 25;
float border = 2;

in VS_OUT {
    float state;
    float value;
} gs_in[];

out GS_OUT {
    vec2 tex_coord;
    vec3 color;
    flat bool has_tex;
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

vec2 pos_offset(vec2 _center, int _pos)
{
    if (_pos == 0)
        return _center + vec2(0.05f, 0.05f);
    if (_pos == 1)
        return _center + vec2(0.05f, -0.05f);
    if (_pos == 2)
        return _center + vec2(-0.05f, 0.05f);
    if (_pos == 3)
        return _center + vec2(-0.05f, -0.05f);
    return _center;
}

vec2 gen_tex_coords(float _state, float _value, int _pos)
{
    if (_state == 0.0f) // Covered
        return pos_offset(vec2(0.05f, 0.75f), _pos);

    if (_state == 1.0f) // Mine Marked
        return pos_offset(vec2(0.25f, 0.85f), _pos);

    // Else we show it
    if (_value >= 0.0f && _value <= 8.0f)
        return pos_offset(vec2(0.05f + 0.1f * _value, 0.95f), _pos);

    if (_value == 10.0f)
        return pos_offset(vec2(0.05f, 0.85f), _pos);
    return pos_offset(vec2(0.05f, 0.95f), _pos);
}

void gen_inner(vec4 _pos, float _state, float _value)
{
    float new_rad = rad - border;

    gl_Position = view * (_pos + vec4(new_rad, new_rad, 0.01f, 0));
    gs_out.tex_coord = gen_tex_coords(_state, _value, 0);
    gs_out.has_tex = true;
    EmitVertex();

    gl_Position = view * (_pos + vec4(new_rad, -1 * new_rad, 0.01f, 0));
    gs_out.tex_coord = gen_tex_coords(_state, _value, 1);
    gs_out.has_tex = true;
    EmitVertex();

    gl_Position = view * (_pos + vec4(-1 * new_rad, new_rad, 0.01f, 0));
    gs_out.tex_coord = gen_tex_coords(_state, _value, 2);
    gs_out.has_tex = true;
    EmitVertex();

    gl_Position = view * (_pos + vec4(-1 * new_rad, -1 * new_rad, 0.01f, 0));
    gs_out.tex_coord = gen_tex_coords(_state, _value, 3);
    gs_out.has_tex = true;
    EmitVertex();
    EndPrimitive();
}
void main() {
    gen_outer(gl_in[0].gl_Position);
    gen_inner(gl_in[0].gl_Position, gs_in[0].state, gs_in[0].value);
}
