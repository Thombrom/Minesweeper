#pragma once
#include <glad/glad.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <string>

#include "Render/Font/FontLibrary.h"
#include "Render/Font/Font.h"

#include "Render/Shader/ShaderLibrary.h"
#include "Render/Shader/Shader.h"

#include "Render/Drawable.h"

class Text : public Drawable
{
public:
    static Text* Create(const std::string& _text, FontType _font_type);
    static void Destroy(Text* _text);

    void set_position(const glm::vec3& _pos);
    void set_center(const glm::vec3& _pos);

    void set_rotation(float _rot);
    void set_scale(const glm::vec2& _scale);
    void set_color(const glm::vec3& _color);
    void set_value(const std::string& _str);

    void draw(const glm::mat4& _view) override;

protected:
    void calculate_transform();
    void calculate_dimensions();

protected:
    Text(const std::string& _text, FontType _font_type);
    std::string m_text;

private:
    // Rendering
    unsigned int m_VAO, m_VBO;
    Shader m_shader;
    Font* m_font;
    glm::mat4 m_transform;

    // Attributes
    glm::vec3 m_color;
    glm::vec3 m_position;
    glm::vec2 m_scale;
    float m_rotation;

    // Data
    unsigned int m_height, m_width;
};
