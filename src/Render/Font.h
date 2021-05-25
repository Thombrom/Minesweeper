#pragma once
#include <glad/glad.h>

#include <map>
#include <iostream>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H  

#include "Render/Shader/Shader.h"

/*
	Wrapper around the FreeFont library
	for more ease of printing text
*/

struct FontChar
{
	unsigned int	texture_id;
	unsigned int	advance;
	glm::ivec2		size;
	glm::ivec2		bearing;
};

class Font
{
public:
	Font();
	void load(const char* _path, uint16_t _width = 0, uint16_t _height = 48);

	void render_text(std::string _text, float _x, float _y, float _scale, glm::vec3 color);

private:
	unsigned int VAO, VBO;

	Shader font_shader;
	std::map<char, FontChar> characters;
};