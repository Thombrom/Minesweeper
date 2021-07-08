#include "SettingsLayer.h"

SettingsLayer::SettingsLayer(Application* _app, uint32_t _pos)
    : Layer(_app, _pos)
{
    border = BorderRect::Create(glm::vec3(-300.0f, -300.0f, 0.0f), glm::vec2(600.0f, 600.0f));
    border->set_inside_color(glm::vec3(0.0f, 0.0f, 0.0f));
    border->set_border_color(glm::vec3(0.0f, 1.0f, 0.0f));

}

SettingsLayer::~SettingsLayer()
{
    BorderRect::Destroy(border);
}

void SettingsLayer::on_push()
{
    std::cout << "Settingslayer Pushed" << std::endl;
}

void SettingsLayer::on_pop()
{
    std::cout << "Settingslayer Popped" << std::endl;
}

void SettingsLayer::on_event(Event& _event)
{

}

void SettingsLayer::on_update()
{
    std::cout << "Drawing Settings Layer" << std::endl;
    glm::mat4 view = app->get_window()->get_orthographic();
    border->draw(view);
}
