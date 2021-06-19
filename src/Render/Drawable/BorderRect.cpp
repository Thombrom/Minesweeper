#pragma once
#include "BorderRect.h"

BorderRect* BorderRect::Create(const glm::vec3 _position, const glm::vec2 _size, unsigned int _border)
{
    return new BorderRect(_position, _size, _border);
}

void BorderRect::Destroy(BorderRect* _rect)
{
    glDeleteBuffers(1, &(_rect->m_VBO));
    glDeleteVertexArrays(1, &(_rect->m_VAO));
    delete _rect;
}

BorderRect::BorderRect(const glm::vec3 _position, const glm::vec2 _size, unsigned int _border)
    : m_size(_size), m_position(_position), m_border(_border) {

    m_shader = ShaderLibrary::Retrieve(ShaderType::BORDER_RECT);

    // Setup default values
    m_color_inside = glm::vec3(0.0f, 0.0f, 0.0f);
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

void BorderRect::buffer_data()
{
    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

    // For convenience
    float x_pos = m_position.x;
    float y_pos = m_position.y;
    float z_pos = m_position.z;
    float w = m_size.x;
    float h = m_size.y;
    float b = m_border;

    float vertex_data[6 * 6 * 2] = {
        x_pos,      y_pos,      0.0f + z_pos,
        m_color_border.x, m_color_border.y, m_color_border.z,
        x_pos + w,  y_pos,      0.0f + z_pos,
        m_color_border.x, m_color_border.y, m_color_border.z,
        x_pos + w,  y_pos + h,  0.0f + z_pos,
        m_color_border.x, m_color_border.y, m_color_border.z,

        x_pos,      y_pos,      0.0f + z_pos,
        m_color_border.x, m_color_border.y, m_color_border.z,
        x_pos,      y_pos + h,  0.0f + z_pos,
        m_color_border.x, m_color_border.y, m_color_border.z,
        x_pos + w,  y_pos + h,  0.0f + z_pos,
        m_color_border.x, m_color_border.y, m_color_border.z,

        x_pos + b,      y_pos + b,      0.001f + z_pos,
        m_color_inside.x, m_color_inside.y, m_color_inside.z,
        x_pos + w - b,  y_pos + b,      0.001f + z_pos,
        m_color_inside.x, m_color_inside.y, m_color_inside.z,
        x_pos + w - b,  y_pos + h - b,  0.001f + z_pos,
        m_color_inside.x, m_color_inside.y, m_color_inside.z,

        x_pos + b,       y_pos + b,      0.001f + z_pos,
        m_color_inside.x, m_color_inside.y, m_color_inside.z,
        x_pos + b,       y_pos + h - b,  0.001f + z_pos,
        m_color_inside.x, m_color_inside.y, m_color_inside.z,
        x_pos + w - b,   y_pos + h - b,  0.001f + z_pos,
        m_color_inside.x, m_color_inside.y, m_color_inside.z,
    };

    // Buffer Data
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void BorderRect::draw(const glm::mat4& _view)
{
    // Render Button Shape
    m_shader.use();
    m_shader.set_mat4("transform", glm::mat4(1.0f));
    m_shader.set_mat4("view", _view);

    glBindVertexArray(m_VAO);
    glDrawArrays(GL_TRIANGLES, 0, 12);
    glBindVertexArray(0);
}

void BorderRect::set_position(const glm::vec3& _position)
{
    if (m_position == _position)
        return;

    m_position = _position;
    buffer_data();
}

void BorderRect::set_size(const glm::vec2& _size)
{
    if (m_size == _size)
        return;

    m_size = _size;
    buffer_data();
}

void BorderRect::set_border(unsigned int _border)
{
    if (m_border == _border)
        return;

    m_border = _border;
    buffer_data();
}

void BorderRect::set_border_color(const glm::vec3& _border_color)
{
    if (m_color_border == _border_color)
        return;

    m_color_border = _border_color;
    buffer_data();
}

void BorderRect::set_inside_color(const glm::vec3& _button_color)
{
    if (m_color_inside == _button_color)
        return;

    m_color_inside = _button_color;
    buffer_data();
}

bool BorderRect::mouse_inside()
{
    float x, y;
    x = Input::MousePosX();
    y = Input::MousePosY();

    return m_position.x < x && m_position.x + m_size.x > x &&
        m_position.y < y && m_position.y + m_size.y > y;
}

bool BorderRect::mouse_outside()
{
    return !mouse_inside();
}

bool BorderRect::mouse_press()
{
    bool res = (Input::Key(MouseCode::Button0) != m_mouse_press) && !m_mouse_press;
    m_mouse_press = Input::Key(MouseCode::Button0);
    return res && mouse_inside();
}

bool BorderRect::mouse_release()
{
    bool res = (Input::Key(MouseCode::Button0) != m_mouse_press) && m_mouse_press;
    m_mouse_press = Input::Key(MouseCode::Button0);
    return res && mouse_inside();
}
