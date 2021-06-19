#pragma once

#include <glad/glad.h>
#include <glm.hpp>
#include <string>
#include <gtc/matrix_transform.hpp>

#include "Event/Event.h"
#include "Application/Input.h"

#include "Render/Shader/ShaderLibrary.h"
#include "Render/Shader/Shader.h"

#include "Render/Font/FontLibrary.h"
#include "Render/Drawable/Text.h"

/*
 * Class for a button which implements
 * click and hover callbacks
 */

class Button : public Drawable
{
public:
    static Button* Create(const glm::vec3 _position, const glm::vec2 _size, const std::string& _text, unsigned int _border = 2);
    static void Destroy(Button* _button);

    void draw(const glm::mat4& _view) override;

    void set_position(const glm::vec3& _position);
    void set_size(const glm::vec2& _size);
    void set_border(unsigned int _border);
    void set_text_scale(float _scale);

    void set_border_color(const glm::vec3& _border_color);
    void set_button_color(const glm::vec3& _button_col);
    void set_text_color(const glm::vec3& _text_color);

    // Event Functions
    bool mouse_inside();
    bool mouse_outside();
    bool mouse_press();
    bool mouse_release();

protected:
    Button(const glm::vec3 _position, const glm::vec2 _size, const std::string& _text, unsigned int _border);

    void buffer_data();

private:
    // Rendering
    unsigned int m_VAO, m_VBO;
    Shader m_shader;
    Text* m_text;

    // Attributes
    glm::vec3 m_color_border;
    glm::vec3 m_color_button;
    glm::vec2 m_size;
    glm::vec3 m_position;
    unsigned int m_border;

    // Functionality
    bool m_mouse_press;
};
