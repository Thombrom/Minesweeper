#pragma once

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <stb_image.h>

#include "Application/Input.h"

#include "Render/Shader/ShaderLibrary.h"
#include "Render/Drawable.h"

class TilePanel : public Drawable
{
public:
	static TilePanel* Create(const glm::vec2 _board_size, uint8_t* _values, uint8_t* _reveal);
	static void Destroy(TilePanel* _panel);

	void set_view(const glm::vec2& _pos, const glm::vec2& _size);
	void draw(const glm::mat4& _view) override;

protected:
	TilePanel(const glm::vec2 _board_size, uint8_t* _values, uint8_t* _reveal);

	void buffer_pos_data();
    void buffer_state_data();
    void buffer_value_data();
    void load_texture();

    int pixelpos_to_tilepos(glm::vec2 _pos);

private:
	uint8_t* m_values, *m_reveal;
	glm::vec2 m_board_size;
    float* state_data;

	// GL values
	glm::vec4 viewport;
	glm::mat4 view;
	unsigned int m_VAO, m_Tex, m_VBO[3];
	Shader shader;
};
