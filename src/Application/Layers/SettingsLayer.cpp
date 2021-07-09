#include "SettingsLayer.h"

SettingsLayer::SettingsLayer(Application* _app, uint32_t _pos)
    : Layer(_app, _pos)
{
	ApplicationData* appdata = (ApplicationData*)app->get_data();
    uint32_t values[3] = { appdata->game_size_x, appdata->game_size_y, appdata->game_mine_count };

    border = BorderRect::Create(glm::vec3(-300.0f, -210.0f, 0.0f), glm::vec2(600.0f, 420.0f));
    border->set_inside_color(glm::vec3(0.0f, 0.0f, 0.0f));
    border->set_border_color(glm::vec3(0.0f, 1.0f, 0.0f));

    divider = BorderRect::Create(glm::vec3(-300.0f, -100.0f, 0.02f), glm::vec2(600.0f, 2.0f));
    divider->set_border_color(glm::vec3(0.0f, 1.0f, 0.0f));
    divider->set_inside_color(glm::vec3(0.0f, 1.0f, 0.0f));

    menu_btn = TextButton::Create("Menu", glm::vec3(-290.0f, -200.0f, 0.01f), glm::vec2(280.0f, 90.0f));
    play_btn = TextButton::Create("Play", glm::vec3(10.0f, -200.0f, 0.01f), glm::vec2(280.0f, 90.0f));

    std::string labels[3] = { "Width", "Height", "Mines" };
    for (size_t itt = 0; itt < 3; itt++) {
        input[itt].text = Text::Create(labels[itt], FontType::ARIAL);
        input[itt].text->set_center(glm::vec3(-150.0f, 150.0f - 100.0f * itt, 0.01f));
        input[itt].text->set_color(glm::vec3(0.0f, 1.0f, 0.0f));

        input[itt].button = TextButton::Create(std::to_string(values[itt]), glm::vec3(10.0f, 110.0f - 100.0f * itt, 0.01f), glm::vec2(280.0f, 90.0f));
    }
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
    EventDispatcher dispatcher(_event);
    dispatcher.execute<MouseButtonPressedEvent>([this](MouseButtonPressedEvent& _e)->bool {
        if (menu_btn->mouse_inside()) {
            app->event_callback(new InternalEvent(InternalEventType::CHANGE_START_MENU, 0));
            return true;
        }

        if (play_btn->mouse_inside()) {
            app->event_callback(new InternalEvent(InternalEventType::CHANGE_START_GAME, 0));
            return true;
        }

        return false;
    });

    dispatcher.execute<MouseScrollEvent>([this](MouseScrollEvent& _e)->bool {
        ApplicationData* appdata = (ApplicationData*)app->get_data();

        if (input[0].button->mouse_inside()) {
            int tmp = appdata->game_size_x + _e.get_y_offset();
            appdata->game_size_x = std::clamp(tmp, 1, GAME_MAX_WIDTH);
            input[0].button->set_text(std::to_string(appdata->game_size_x));
            return true;
        }

        if (input[1].button->mouse_inside()) {
            int tmp = appdata->game_size_y + _e.get_y_offset();
            appdata->game_size_y = std::clamp(tmp, 1, GAME_MAX_HEIGHT);
            input[1].button->set_text(std::to_string(appdata->game_size_y));
            return true;
        }

        if (input[2].button->mouse_inside()) {
            int tmp = appdata->game_mine_count + _e.get_y_offset();
            appdata->game_mine_count = std::clamp(tmp, 1, (int)(0.5 * appdata->game_size_x * appdata->game_size_y));
            input[2].button->set_text(std::to_string(appdata->game_mine_count));
            return true;
        }

        return false;
    });

}

void SettingsLayer::on_update()
{
    glm::mat4 view = app->get_window()->get_orthographic();
    border->draw(view);
    divider->draw(view);

    menu_btn->draw(view);
    play_btn->draw(view);

    for (size_t itt = 0; itt < 3; itt++) {
        input[itt].text->draw(view);
        input[itt].button->draw(view);
    }
}
