#pragma once

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include "Application/Input.h"

#include "Render/Shader/ShaderLibrary.h"
#include "Render/Drawable.h"

class TilePanel : public Drawable
{
public:
	static TilePanel* Create(const glm::vec2 _board_size, uint8_t* _values, uint8_t* _reveal);
	static void Destroy(TilePanel* _panel);

	void update_hover(const glm::vec2 _pos);
	void update_press(const glm::vec2 _pos);

	void set_view(const glm::vec2& _pos, const glm::vec2& _size);
	void draw(const glm::mat4& _view) override;

protected:
	TilePanel(const glm::vec2 _board_size, uint8_t* _values, uint8_t* _reveal);

	void buffer_data();

private:
	uint8_t* m_values, *m_reveal;
	glm::vec2 m_board_size;

	// GL values
	glm::vec4 viewport;
	glm::mat4 view;
	unsigned int m_VAO, m_VBO;
	Shader shader;
	uint8_t* vertex_data;
};