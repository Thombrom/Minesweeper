#include "MenuLayer.h"

MenuLayer::MenuLayer(Application* _app, uint32_t _position)
    : Layer(_app, _position) {
    
    std::string texts[3] = {
        "Play Game",
        "Settings",
        "Exit Game"
    };

    // Style buttons
    for (size_t itt = 0; itt < sizeof(button_panel) / sizeof(TextButton); itt++)
    {
        button_panel[itt] = TextButton{
            BorderRect::Create(glm::vec3(-200.0f, 60.0f - 100.0f * itt, 0.0f), glm::vec2(400.0f, 80.0f), 2),
            Text::Create(texts[itt], FontType::ARIAL),
        };

        button_panel[itt].text->set_center(glm::vec3(0.0f, 100.0f - 100.0f * itt, 0.01f));
        button_panel[itt].rect->set_border_color(glm::vec3(0.0f, 1.0f, 0.0f));
        button_panel[itt].rect->set_inside_color(glm::vec3(0.0f, 0.0f, 0.0f));
        button_panel[itt].text->set_color(glm::vec3(0.0f, 1.0f, 0.0f));
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
    for (size_t itt = 0; itt < sizeof(button_panel) / sizeof(TextButton); itt++)
    {
        BorderRect::Destroy(button_panel[itt].rect);
        Text::Destroy(button_panel[itt].text);
    }
}

void MenuLayer::on_update()
{
    for (size_t itt = 0; itt < sizeof(button_panel) / sizeof(TextButton); itt++) {
        if (button_panel[itt].rect->mouse_inside()) {
            button_panel[itt].rect->set_inside_color(glm::vec3(0.0f, 1.0f, 0.0f));
            button_panel[itt].text->set_color(glm::vec3(0.0f, 0.0f, 0.0f));
        }
        else {
            button_panel[itt].rect->set_inside_color(glm::vec3(0.0f, 0.0f, 0.0f));
            button_panel[itt].text->set_color(glm::vec3(0.0f, 1.0f, 0.0f));
        }

        if (button_panel[itt].rect->mouse_press()) {
            app->event_callback(new InternalEvent(button_click_event[itt], 0));
        }

        button_panel[itt].rect->draw(app->get_window()->get_orthographic());
        button_panel[itt].text->draw(app->get_window()->get_orthographic());
    }
}

void MenuLayer::on_event(Event& _event)
{
}




