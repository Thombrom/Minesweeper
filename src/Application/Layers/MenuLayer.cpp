#include "MenuLayer.h"

MenuLayer::MenuLayer(Application* _app, uint32_t _position)
    : Layer(_app, _position) {

    button_panel[0] = Button::Create(glm::vec3(-200.0f, 60.0f, 0.0f), glm::vec2(400.0f, 80.0f), "Play Game", 2);
    button_panel[1] = Button::Create(glm::vec3(-200.0f, -40.0f, 0.0f), glm::vec2(400.0f, 80.0f), "Settings", 2);
    button_panel[2] = Button::Create(glm::vec3(-200.0f, -140.0f, 0.0f), glm::vec2(400.0f, 80.0f), "Exit", 2);

    // Style buttons
    for (size_t itt = 0; itt < sizeof(button_panel) / sizeof(Button*); itt++)
    {
        button_panel[itt]->set_border_color(glm::vec3(0.0f, 1.0f, 0.0f));
        button_panel[itt]->set_button_color(glm::vec3(0.0f, 0.0f, 0.0f));
        button_panel[itt]->set_text_color(glm::vec3(0.0f, 1.0f, 0.0f));
    }

    button_click_event[0] = InternalEventType::CHANGE_START_GAME;
    button_click_event[1] = InternalEventType::CHANGE_START_SETTINGS;
    button_click_event[2] = InternalEventType::EXIT_APP;
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
    for (size_t itt = 0; itt < sizeof(button_panel) / sizeof(Button*); itt++) {
        if (button_panel[itt]->mouse_inside()) {
            button_panel[itt]->set_button_color(glm::vec3(0.0f, 1.0f, 0.0f));
            button_panel[itt]->set_text_color(glm::vec3(0.0f, 0.0f, 0.0f));
        }
        else {
            button_panel[itt]->set_button_color(glm::vec3(0.0f, 0.0f, 0.0f));
            button_panel[itt]->set_text_color(glm::vec3(0.0f, 1.0f, 0.0f));
        }

        if (button_panel[itt]->mouse_press()) {
            app->event_callback(new InternalEvent(button_click_event[itt], 0));
        }

        button_panel[itt]->draw(app->get_window()->get_orthographic());
    }
}

void MenuLayer::on_event(Event& _event)
{
}




