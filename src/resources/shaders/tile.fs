#version 330 core
out vec4 FragColor;

in GS_OUT {
    vec2 tex_coord;
    vec3 color;
    flat bool has_tex;
} fs_in;

void main()
{
    FragColor = vec4(fs_in.color, fs_in.has_tex ? 0 : 1);
    //FragColor = vec4(0.0f, 1.0f, 0.0f, 1.0f);
}
