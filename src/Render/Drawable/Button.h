#pragma once

#include <glad/glad.h>
#include <glm.hpp>
#include <string>
#include <gtc/matrix_transform.hpp>

#include "Event/Event.h"

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
    static Button* Create(const glm::vec2 _position, const glm::vec2 _size, const std::string& _text, unsigned int _border = 2);
    ~Button();

    void draw(const glm::mat4& _view) override;

    void set_position(const glm::vec3& _position);
    void set_size(const glm::vec3& _size);
    void set_border(unsigned int _border);
    void set_text_scale(float _scale);

    void set_border_color(const glm::vec3& _border_color);
    void set_button_color(const glm::vec3& _button_color);
    void set_text_color(const glm::vec3& _text_color);

protected:
    Button(const glm::vec2 _position, const glm::vec2 _size, const std::string& _text, unsigned int _border);

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
    glm::vec2 m_position;
    unsigned int m_border;
};
