#include "Text.h"

Text* Text::Create(const std::string& _text, FontType _font_type)
{
    return new Text(_text, _font_type);
}

Text::Text(const std::string& _text, FontType _font_type) 
    : m_text(_text) {
    // Initialize Values
    m_shader    = ShaderLibrary::Retrieve(ShaderType::TEXT);
    m_font      = FontLibrary::Retrieve(_font_type);
    m_transform = glm::mat4(1.0f);

    m_rotation  = 0.0f;
    m_position  = glm::vec3(0.0f, 0.0f, 0.0f);
    m_scale     = glm::vec2(1.0f, 1.0f);
    m_color     = glm::vec3(1.0f, 1.0f, 1.0f);
    
    // Calculate Dimensions
    calculate_dimensions();

    // Create Buffers
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);

    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);

	// Reset buffers
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

Text::~Text()
{
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
}

void Text::draw(const glm::mat4& _view)
{
    m_shader.use();
    m_shader.set_vec3("text_color", m_color.x, m_color.y, m_color.z);
    m_shader.set_mat4("view", _view);
    m_shader.set_mat4("transform", m_transform);

    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(m_VAO);

    float base_x = 0;
    for (char c : m_text)
    {
        FontChar ch = m_font->get_char(c);

        float xpos = base_x + ch.bearing.x * m_scale.x;
        float ypos = 0 - (ch.size.y - ch.bearing.y) * m_scale.y;

        float w = ch.size.x * m_scale.x;
        float h = ch.size.y * m_scale.y;

        float vertices[6][4] = {
            { xpos,		ypos + h,	0.0f, 0.0f },
            { xpos,		ypos,		0.0f, 1.0f },
            { xpos + w,	ypos,		1.0f, 1.0f },

            { xpos,		ypos + h,	0.0f, 0.0f },
            { xpos + w,	ypos,		1.0f, 1.0f },
            { xpos + w, ypos + h,	1.0f, 0.0f },
        };

        glBindTexture(GL_TEXTURE_2D, ch.texture_id);
        m_shader.set_int("char_map", 0);

        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        base_x += (ch.advance >> 6) * m_scale.x;
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Text::set_position(const glm::vec3& _position)
{
    m_position = _position;
    calculate_transform();
}

void Text::set_center(const glm::vec3& _position)
{
    /*float rad_rot = glm::radians(m_rotation);

    glm::ivec2 opp_corner = glm::ivec2(
        (unsigned int)(m_width * cos(rad_rot) - m_height * sin(rad_rot)),
        (unsigned int)(m_width * sin(rad_rot) + m_height * cos(rad_rot))
    );

    std::cout << "Opp Corner: (" << opp_corner.x << ", " << opp_corner.y << ")" << std::endl;

    glm::ivec2 offset = glm::ivec2(
        (_position.x - opp_corner.y) / 2,
        (_position.y - opp_corner.y) / 2
    );

    std::cout << "Dimensions: (" << m_width << ", " << m_height << ")" << std::endl;
    std::cout << "Offest:     (" << offset.x << ", " << offset.y << ")" << std::endl;

    set_position(offset);*/
    // TODO: Make the center work with rotations

    set_position(glm::vec3(_position.x - m_width / 2, _position.y - m_height / 2, _position.z));
}

void Text::set_rotation(float _rotation)
{
    m_rotation = _rotation;
    calculate_transform();
}

void Text::set_scale(const glm::vec2& _scale)
{
    m_scale = _scale;
    calculate_transform();
}

void Text::set_color(const glm::vec3& _color)
{
    m_color = _color;
}

void Text::calculate_transform()
{
    m_transform = glm::mat4(1.0f);
    m_transform = glm::translate(m_transform, m_position);
    m_transform = glm::rotate(m_transform, glm::radians(m_rotation), glm::vec3(0.0f, 0.0f, 1.0f));
    m_transform = glm::scale(m_transform, glm::vec3(m_scale.x, m_scale.y, 1.0f));
}

void Text::calculate_dimensions()
{
    unsigned int top = 0, bottom = 0;
    m_height = 0; m_width = 0;

    for (char c : m_text)
    {
        FontChar font_char = m_font->get_char(c);
        bottom    = (bottom < font_char.size.y - font_char.bearing.y ? font_char.size.y - font_char.bearing.y : bottom);
        top       = (top < font_char.bearing.y ? font_char.bearing.y : top);
        m_width   += (font_char.advance >> 6) * m_scale.x;
    }

    m_height = (bottom + top) * m_scale.y;
}
