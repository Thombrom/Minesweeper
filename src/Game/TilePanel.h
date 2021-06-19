#pragma once

#include <glm.hpp>

#include "Render/Drawable.h"

class TilePanel : public Drawable
{
public:
	TilePanel();
	void initialize(const glm::vec2 _board_size, uint8_t* _values, uint8_t* _reveal);

	void update_hover(const glm::vec2 _pos);
	void update_press(const glm::vec2 _pos);

	void draw(const glm::mat4& _view) override;

private:
	uint8_t* m_values, m_reveal, m_hover;
	glm::vec2 m_board_size;
};