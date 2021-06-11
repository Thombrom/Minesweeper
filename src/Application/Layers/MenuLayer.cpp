#include "MenuLayer.h"

MenuLayer::MenuLayer(Application* _app, uint32_t _position)
    : Layer(_app, _position) {

    button_panel[0] = Button::Create(glm::vec2(200.0f, 500.0f), glm::vec2(200.0f, 80.0f), "Button 0", 2);
    button_panel[1] = Button::Create(glm::vec2(200.0f, 400.0f), glm::vec2(200.0f, 80.0f), "Button 1", 2);
    button_panel[2] = Button::Create(glm::vec2(200.0f, 300.0f), glm::vec2(200.0f, 80.0f), "Button 2", 2);

    // Style buttons
    for (size_t itt = 0; itt < sizeof(button_panel) / sizeof(Button*); itt++)
    {
        button_panel[itt]->set_border_color(glm::vec3(0.0f, 1.0f, 0.0f));
        button_panel[itt]->set_button_color(glm::vec3(0.0f, 0.0f, 0.0f));
        button_panel[itt]->set_text_color(glm::vec3(0.0f, 1.0f, 0.0f));
    }
}

MenuLayer::~MenuLayer()
{
    std::cout << "Menu Layer destroyed" << std::endl;
}

void MenuLayer::on_push()
{
    std::cout << "Menu Layer Pushed" << std::endl;
}

void MenuLayer::on_pop()
{
    std::cout << "Menu Layer Popped" << std::endl;
}

void MenuLayer::on_update()
{
    for (size_t itt = 0; itt < sizeof(button_panel) / sizeof(Button*); itt++)
        button_panel[itt]->draw(glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f));
}

void MenuLayer::on_event(Event& _event)
{
}




