#version 330 core
in vec2 TexCoords;
out vec4 FragColor;

uniform sampler2D char_map;
uniform vec3 text_color;

void main()
{    
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(char_map, TexCoords).r);
    FragColor = vec4(text_color, 1.0) * sampled;
}  
