#pragma once
#include <string>
#include <glm.hpp>

#include "Render/Drawable.h"
#include "Render/Drawable/Text.h"
#include "Render/Drawable/BorderRect.h"

class TextButton : public Drawable
{
public:
    static TextButton* Create(std::string _str, const glm::vec3& _pos, const glm::vec2& _size);
    static void Destroy(TextButton* _btn);

    void set_border_color(const glm::vec3& _color);
    void set_inside_color(const glm::vec3& _color);
    void set_text_color(const glm::vec3& _color);

    void set_inside_color_hover(const glm::vec3& _color) { m_inside_color_hover = _color; }
    void set_text_color_hover(const glm::vec3& _color) { m_text_color_hover = _color; }
    void set_text(const std::string& _str) { m_text->set_value(_str); }

    void draw(const glm::mat4& _view);

    bool mouse_press() { return m_border->mouse_press(); }
    bool mouse_release() { return m_border->mouse_release(); }
    bool mouse_inside() { return m_border->mouse_inside(); }
    bool mouse_outside() { return m_border->mouse_outside(); }

protected:
    TextButton(std::string _str, const glm::vec3& _pos, const glm::vec2& _size);


protected:
    Text* m_text;
    BorderRect* m_border;

    glm::vec3 m_inside_color;
    glm::vec3 m_text_color;
    glm::vec3 m_inside_color_hover;
    glm::vec3 m_text_color_hover;
};
