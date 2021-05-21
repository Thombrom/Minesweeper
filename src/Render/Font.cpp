#include "Font.h"

Font::Font()
{
	// Initialize shader
	font_shader.set_vertex_shader("resources/shaders/font_vertex.vs");
	font_shader.set_fragment_shader("resources/shaders/font_fragment.fs");
	font_shader.compile();

	// Set up vertex arrays
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);

	// Reset buffers
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

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

void Font::render_text(std::string _text, float _x, float _y, float _scale, glm::vec3 _color)
{
	font_shader.use();

	// For now we also set the projection here
	font_shader.set_vec3("textColor", _color.x, _color.y, _color.z);
	font_shader.set_mat4("projection", glm::ortho(0.0f, 800.0f, 0.0f, 600.0f));
		
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(VAO);

	for (char c : _text)
	{
		FontChar ch = characters[c];
	
		float xpos = _x + ch.bearing.x * _scale;
		float ypos = _y - (ch.size.y - ch.bearing.y) * _scale;

		float w = ch.size.x * _scale;
		float h = ch.size.y * _scale;

		float vertices[6][4] = {
			{ xpos,		ypos + h,	0.0f, 0.0f },
			{ xpos,		ypos,		0.0f, 1.0f },
			{ xpos + w,	ypos,		1.0f, 1.0f },

			{ xpos,		ypos + h,	0.0f, 0.0f },
			{ xpos + w,	ypos,		1.0f, 1.0f },
			{ xpos + w, ypos + h,	1.0f, 0.0f },
		};

		glBindTexture(GL_TEXTURE_2D, ch.texture_id);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		_x += (ch.advance >> 6) * _scale;
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}