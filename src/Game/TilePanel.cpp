#include "TilePanel.h"

TilePanel* TilePanel::Create(const glm::vec2 _board_size, uint8_t* _values, uint8_t* _reveal)
{
	return new TilePanel(_board_size, _values, _reveal);
}

void TilePanel::Destroy(TilePanel* _panel)
{
    delete[] _panel->state_data;
	glDeleteBuffers(3, _panel->m_VBO);
	glDeleteVertexArrays(1, &_panel->m_VAO);
    glDeleteTextures(1, &_panel->m_Tex);
}

TilePanel::TilePanel(const glm::vec2 _board_size, uint8_t* _values, uint8_t* _reveal)
{
	shader = ShaderLibrary::Retrieve(ShaderType::TILE);
	m_board_size = _board_size;
	m_values = _values;
	m_reveal = _reveal;

	glGenBuffers(3, m_VBO);
	glGenVertexArrays(1, &m_VAO);
    glGenTextures(1, &m_Tex);

    // Create our dynamic buffer
	buffer_pos_data();
    buffer_state_data();
    buffer_value_data();
    load_texture();

	glBindVertexArray(m_VAO);
	glBindVertexArray(0);
}

void TilePanel::buffer_pos_data()
{
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO[0]);

	// Buffer data
    uint32_t buffer_size = 3 * m_board_size.x * m_board_size.y;
    float* vdata = new float[buffer_size];
	for (size_t itt_y = 0; itt_y < m_board_size.y; itt_y++)
	{
		for (size_t itt_x = 0; itt_x < m_board_size.x; itt_x++)
		{
			float size_x = 52;
			float size_y = 52;

			float total_x = 52 * m_board_size.x;
			float total_y = 52 * m_board_size.y;

			float* pos_ptr = vdata + 3 * ((uint8_t)m_board_size.x * itt_y + itt_x);
			
			pos_ptr[0] = size_x * itt_x - total_x / 2 + size_x / 2;
			pos_ptr[1] = size_y* itt_y - total_y / 2 + size_y / 2;
			pos_ptr[2] = 0.01f;
		}
	}
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * buffer_size, vdata, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

    delete vdata;
    glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void TilePanel::buffer_state_data()
{
    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO[1]);

    uint32_t buffer_size = m_board_size.x * m_board_size.y;
    state_data = new float[buffer_size];
    for (size_t itt = 0; itt < buffer_size; itt++)
        state_data[itt] = 0.00f;

    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * buffer_size, state_data, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void TilePanel::buffer_value_data()
{
    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO[2]);

    uint32_t buffer_size = m_board_size.x * m_board_size.y;
    float* value_data = new float[buffer_size];
    for (size_t itt = 0; itt < m_board_size.x * m_board_size.y; itt++) 
        value_data[itt] = (float)m_values[itt];

    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * buffer_size, value_data, GL_STATIC_DRAW);
    glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(float), (void*)0);
    glEnableVertexAttribArray(2);

    delete value_data;
    glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void TilePanel::load_texture() {
    glBindTexture(GL_TEXTURE_2D, m_Tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    int width, height, channels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load("resources/textures/minesweeper.png", &width, &height, &channels, 0);
    if (data) {
        std::cout << "Loaded Texture" << std::endl;
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "Unable to load texture" << std::endl;
    }
    stbi_image_free(data);
}

void TilePanel::reload_state() {
    uint32_t buffer_size = m_board_size.x * m_board_size.y;
    for (size_t itt = 0; itt < buffer_size; itt++)
        state_data[itt] = (float)m_reveal[itt];

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, buffer_size * sizeof(float), state_data, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void TilePanel::set_view(const glm::vec2& _pos, const glm::vec2& _size)
{
	view = glm::ortho(_size.x / -2, _size.x / 2, _size.y / -2, _size.y / 2);
	viewport = glm::vec4(
		Input::WindowWidth() / 2 + _pos.x, 
		Input::WindowHeight() / 2 + _pos.y, 
		_size.x,
		_size.y
	);
}

void TilePanel::draw(const glm::mat4& _trans)
{
	shader.use();
	shader.set_mat4("view", view * _trans);
	shader.set_vec3("border_color", 0.0f, 1.0f, 0.0f);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_Tex);
    shader.set_int("tex_map", 0);

	glViewport(viewport.x, viewport.y, viewport.z, viewport.w);
	glBindVertexArray(m_VAO);
	glDrawArrays(GL_POINTS, 0, m_board_size.x * m_board_size.y);
	glBindVertexArray(0);
	glViewport(0, 0, Input::WindowWidth(), Input::WindowHeight());
}
