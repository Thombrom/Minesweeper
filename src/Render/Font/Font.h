#pragma once
#include <glad/glad.h>

#include <map>
#include <iostream>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "Render/Shader/Shader.h"
#include "Render/Shader/ShaderLibrary.h"

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
    Font() = default;

    void load(const char* _path, uint16_t _width = 0, uint16_t _height = 48);
    FontChar& get_char(char _c) { return characters.at(_c); };

private:
	std::map<char, FontChar> characters;
};
