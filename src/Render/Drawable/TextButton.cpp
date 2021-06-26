#include "TextButton.h"

TextButton::TextButton(std::string _str, const glm::vec3& _pos, const glm::vec2& _size)
{
    m_text = Text::Create(_str, FontType::ARIAL);
    m_text->set_center(glm::vec3(_pos.x + _size.x / 2, _pos.y + _size.y / 2, _pos.z + 0.01f));
    m_text->set_color(glm::vec3(0.0f, 1.0f, 0.0f));

    m_border = BorderRect::Create(_pos, _size);
    m_border->set_inside_color(glm::vec3(0.0f, 0.0f, 0.0f));
    m_border->set_border_color(glm::vec3(0.0f, 1.0f, 0.0f));

    m_inside_color       = glm::vec3(0.0f, 0.0f, 0.0f);
    m_text_color         = glm::vec3(0.0f, 1.0f, 0.0f);
    m_inside_color_hover = glm::vec3(0.0f, 1.0f, 0.0f);
    m_text_color_hover   = glm::vec3(0.0f, 0.0f, 0.0f);
}

TextButton* TextButton::Create(std::string _str, const glm::vec3& _pos, const glm::vec2& _size)
{
    return new TextButton(_str, _pos, _size);
}

void TextButton::Destroy(TextButton* _btn)
{
    Text::Destroy(_btn->m_text);
    BorderRect::Destroy(_btn->m_border);
}

void TextButton::set_inside_color(const glm::vec3& _color)
{
    m_inside_color = _color;
    m_border->set_inside_color(_color);
}

void TextButton::set_border_color(const glm::vec3& _color)
{
    m_border->set_border_color(_color);
}

void TextButton::set_text_color(const glm::vec3& _color)
{
    m_text_color = _color;
    m_text->set_color(_color);
}

void TextButton::draw(const glm::mat4& _view)
{
    // Update hovering
    if (m_border->mouse_inside())
    {
        m_text->set_color(m_text_color_hover);
        m_border->set_inside_color(m_inside_color_hover);
    }
    else
    {
        m_text->set_color(m_text_color);
        m_border->set_inside_color(m_inside_color);
    }

    m_border->draw(_view);
    m_text->draw(_view);
}
