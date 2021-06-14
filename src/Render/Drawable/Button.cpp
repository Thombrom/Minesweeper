#include "Button.h"

Button* Button::Create(const glm::vec2 _position, const glm::vec2 _size, const std::string& _text, unsigned int _border)
{
    return new Button(_position, _size, _text, _border);
}

Button::Button(const glm::vec2 _position, const glm::vec2 _size, const std::string& _text, unsigned int _border)
    : m_size(_size), m_position(_position), m_border(_border) {

    m_text = Text::Create(_text, FontType::ARIAL);
    m_text->set_center(glm::ivec3(_position.x + _size.x / 2, _position.y + _size.y / 2, 0.2f));
    m_shader = ShaderLibrary::Retrieve(ShaderType::BUTTON);

    // Setup default values
    m_color_button = glm::vec3(0.0f, 0.0f, 0.0f);
    m_color_border = glm::vec3(1.0f, 1.0f, 1.0f);


    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    buffer_data();

    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(0));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(0 + sizeof(float) * 3));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Button::buffer_data()
{
    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

    // For convenience
    float x_pos = m_position.x;
    float y_pos = m_position.y;
    float w     = m_size.x;
    float h     = m_size.y;
    float b     = m_border;

    float vertex_data[6 * 6 * 2] = {
        x_pos,      y_pos,      0.0f,
        m_color_border.x, m_color_border.y, m_color_border.z,
        x_pos + w,  y_pos,      0.0f,
        m_color_border.x, m_color_border.y, m_color_border.z,
        x_pos + w,  y_pos + h,  0.0f,
        m_color_border.x, m_color_border.y, m_color_border.z,

        x_pos,      y_pos,      0.0f,
        m_color_border.x, m_color_border.y, m_color_border.z,
        x_pos,      y_pos + h,  0.0f,
        m_color_border.x, m_color_border.y, m_color_border.z,
        x_pos + w,  y_pos + h,  0.0f,
        m_color_border.x, m_color_border.y, m_color_border.z,

        x_pos + b,      y_pos + b,      0.1f,
        m_color_button.x, m_color_button.y, m_color_button.z,
        x_pos + w - b,  y_pos + b,      0.1f,
        m_color_button.x, m_color_button.y, m_color_button.z,
        x_pos + w - b,  y_pos + h - b,  0.1f,
        m_color_button.x, m_color_button.y, m_color_button.z,

        x_pos + b,       y_pos + b,      0.1f,
        m_color_button.x, m_color_button.y, m_color_button.z,
        x_pos + b,       y_pos + h - b,  0.1f,
        m_color_button.x, m_color_button.y, m_color_button.z,
        x_pos + w - b,   y_pos + h - b,  0.1f,
        m_color_button.x, m_color_button.y, m_color_button.z,
    };

    // Buffer Data
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Button::draw(const glm::mat4& _view)
{
    // Render Button Shape
    m_shader.use();
    m_shader.set_mat4("transform", glm::mat4(1.0f));
    m_shader.set_mat4("view", _view);

    glBindVertexArray(m_VAO);
    glDrawArrays(GL_TRIANGLES, 0, 12);
    glBindVertexArray(0);

    // Render Button Text
    m_text->draw(_view);
}

void Button::set_position(const glm::vec3& _position)
{
    if (m_position == _position)
        return;

    m_position = _position;
    buffer_data();
}

void Button::set_size(const glm::vec3& _size)
{
    if (m_size == _size)
        return;

    m_size = _size;
    buffer_data();
}

void Button::set_border(unsigned int _border)
{
    if (m_bordre == _border)
        return;

    m_border = _border;
    buffer_data();
}

void Button::set_text_scale(float _scale)
{
    m_text->set_scale(glm::vec2(_scale));
}

void Button::set_border_color(const glm::vec3& _border_color)
{
    if (m_color_border == _border_color)
        return;

    m_color_border = _border_color;
    buffer_data();
}

void Button::set_button_color(const glm::vec3& _button_color)
{
    if (m_button_color == _button_color)
        return;

    m_color_button = _button_color;
    buffer_data();
}

void Button::set_text_color(const glm::vec3& _text_color)
{
    m_text->set_color(_text_color);
}

bool Button::mouse_inside(MouseMovedEvent& _event)
{
    float x, y;
    x = _event.get_x();
    y = _event.get_y();

    return m_position.x < x && m_position.x + m_size.x > x &&
           m_position.y < y && m_position.y + m_size.y > y;
}

bool Button::mouse_outside(MouseMovedEvent& _event)
{
    return !mouse_inside(_event);
}

bool Button::mouse_press(MouseKeyPressedEvent& _event)
{

}

bool Button::mouse_release(MouseKeyReleasedEvent& _event)
{

}
