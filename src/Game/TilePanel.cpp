#include "TilePanel.h"

TilePanel* TilePanel::Create(const glm::vec2 _board_size, uint8_t* _values, uint8_t* _reveal)
{
	return new TilePanel(_board_size, _values, _reveal);
}

void TilePanel::Destroy(TilePanel* _panel)
{
	free(_panel->vertex_data);
	glDeleteBuffers(1, &_panel->m_VBO);
	glDeleteVertexArrays(1, &_panel->m_VAO);
}

TilePanel::TilePanel(const glm::vec2 _board_size, uint8_t* _values, uint8_t* _reveal)
{
	shader = ShaderLibrary::Retrieve(ShaderType::TILE);
	m_board_size = _board_size;
	m_values = _values;
	m_reveal = _reveal;

	glGenBuffers(1, &m_VBO);
	glGenVertexArrays(1, &m_VAO);
	buffer_data();

	glBindVertexArray(m_VAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//glVertexAttribPointer(1, 1, GL_UNSIGNED_INT, GL_FALSE, 3 * sizeof(float) + 2 * sizeof(unsigned int), (void*)(0 + sizeof(float) * 3));
	//glEnableVertexAttribArray(1);
	//glVertexAttribPointer(2, 1, GL_UNSIGNED_INT, GL_FALSE, 3 * sizeof(float) + 2 * sizeof(unsigned int), (void*)(0 + sizeof(float) * 3 + sizeof(unsigned int)));
	//glEnableVertexAttribArray(2);
	glBindVertexArray(0);
}

void TilePanel::buffer_data()
{
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	// Buffer data
	//vertex_data = (uint8_t*)malloc((3 * sizeof(float)) * m_board_size.x * m_board_size.y);
	float vdata[300] = { 0.0f };
	for (size_t itt_y = 0; itt_y < m_board_size.y; itt_y++)
	{
		for (size_t itt_x = 0; itt_x < m_board_size.x; itt_x++)
		{
			float size_x = 52;
			float size_y = 52;

			float total_x = 52 * m_board_size.x;
			float total_y = 52 * m_board_size.y;

			//float* pos_ptr = vdata + 3 * ((uint8_t)m_board_size.x * itt_y + itt_x);//(float*)(vertex_data + (3 * sizeof(float)) * ((uint8_t)m_board_size.x * itt_y + itt_x));
			float* pos_ptr = vdata + 3 * ((uint8_t)m_board_size.x * itt_y + itt_x);
			
			pos_ptr[0] = size_x * itt_x - total_x / 2 + size_x / 2;
			pos_ptr[1] = size_y* itt_y - total_y / 2 + size_y / 2;
			pos_ptr[2] = 0.01f;

			//unsigned int* attr_ptr = (unsigned int*)(vertex_data + (3 * sizeof(float) + 2 * sizeof(unsigned int)) * ((uint8_t)m_board_size.x * itt_y + itt_x) + 3 * sizeof(float));
			//attr_ptr[0] = m_reveal[(uint8_t)m_board_size.x * itt_y + itt_x];
			//attr_ptr[1] = m_values[(uint8_t)m_board_size.x * itt_y + itt_x];
		}
	}

	for (size_t itt = 0; itt < m_board_size.x * m_board_size.y; itt++)
	{
		float* pos_ptr = vdata + 3 * itt;
		std::cout << "(" << pos_ptr[0] << ", " << pos_ptr[1] << ", " << pos_ptr[2] << ")" << std::endl;
	}

	//float vdata[6] = {
	//	-25.0f, 0.0f, 0.01f,
	//	25.0f, 0.0f, 0.01f
	//};

	glBufferData(GL_ARRAY_BUFFER, sizeof(vdata), vdata, GL_STATIC_DRAW);
	glBindVertexArray(0);
}

void TilePanel::set_view(const glm::vec2& _pos, const glm::vec2& _size)
{
	view = glm::ortho(_pos.x, _pos.x + _size.x, _pos.y, _pos.y + _size.y);
	viewport = glm::vec4(
		Input::WindowWidth() / 2 + _pos.x, 
		Input::WindowHeight() / 2 + _pos.y, 
		_size.x, 
		_size.y
	);
}

void TilePanel::update_hover(const glm::vec2 _pos)
{

}

void TilePanel::update_press(const glm::vec2 _pos)
{

}

void TilePanel::draw(const glm::mat4& _view)
{
	shader.use();
	shader.set_mat4("view", view);
	shader.set_vec3("border_color", 0.0f, 1.0f, 0.0f);

	glViewport(viewport.x, viewport.y, viewport.z, viewport.w);
	glBindVertexArray(m_VAO);
	glDrawArrays(GL_POINTS, 0, 100);
	glBindVertexArray(0);
	glViewport(0, 0, Input::WindowWidth(), Input::WindowHeight());
}