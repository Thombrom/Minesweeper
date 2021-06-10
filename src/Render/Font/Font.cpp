#include "Font.h"

void Font::load(const char* _path, uint16_t _width, uint16_t _height)
{
	FT_Library	font_library;
	FT_Face		font_face;

	if (FT_Init_FreeType(&font_library))
	{
		std::cout << "ERROR::FREETYPE: Could not initialize freetype library" << std::endl;
	}

	if (FT_New_Face(font_library, _path, 0, &font_face))
	{
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
	}

	FT_Set_Pixel_Sizes(font_face, _width, _height);

	// Load ASCII 0-127
	for (unsigned char c = 0; c < 128; c++)
	{
		// Load glypy
		if (FT_Load_Char(font_face, c, FT_LOAD_RENDER))
		{
			std::cout << "ERROR::FREETYPE: Failed to load glyph '" << c << "'" << std::endl;
			continue;
		}

		// Format it as bitmap
		unsigned int texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			font_face->glyph->bitmap.width,
			font_face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			font_face->glyph->bitmap.buffer
		);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// Store in library
		FontChar character = {
			 texture,
			 font_face->glyph->advance.x,
			 glm::ivec2(font_face->glyph->bitmap.width, font_face->glyph->bitmap.rows),
			 glm::ivec2(font_face->glyph->bitmap_left,  font_face->glyph->bitmap_top),
		};
		characters.insert(std::pair<char, FontChar>(c, character));
	}

	FT_Done_Face(font_face);
	FT_Done_FreeType(font_library);
}
