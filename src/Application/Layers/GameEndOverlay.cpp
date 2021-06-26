#include "GameEndOverlay.h"

GameEndOverlay::GameEndOverlay(Application* _app, uint32_t _pos, uint32_t _state)
    : Layer(_app, _pos)
{
    // Create Message
    std::string msg = "Not Set";
    if (_state == 1)
        msg = "You Won!";
    if (_state == 2)
        msg = "You Lost!";
    message = Text::Create(msg, FontType::ARIAL);
    message->set_center(glm::vec3(0.0f, 50.0f, 0.11f));
    message->set_color(glm::vec3(0.0f, 1.0f, 0.0f));

    // Create border
    border  = BorderRect::Create(glm::vec3(-200.0f, -130.0f, 0.10f), glm::vec2(400.0f, 260.0f));
    border->set_inside_color(glm::vec3(0.0f, 0.0f, 0.0f));
    border->set_border_color(glm::vec3(0.0f, 1.0f, 0.0f));

    menu_button = TextButton::Create("Menu", glm::vec3(-190.0f, -120.0f, 0.11f), glm::vec2(180.0f, 80.0f));
    redo_button = TextButton::Create("Again", glm::vec3(10.0f, -120.0f, 0.11f), glm::vec2(180.0f, 80.0f));
}

GameEndOverlay::~GameEndOverlay()
{
    Text::Destroy(message);
    BorderRect::Destroy(border);

    TextButton::Destroy(menu_button);
    TextButton::Destroy(redo_button);
}

void GameEndOverlay::on_push() {
    std::cout << "GameEndOverlay Pushed" << std::endl;
}

void GameEndOverlay::on_pop() {
    std::cout << "GameEndOverlay Popped" << std::endl;
}

void GameEndOverlay::on_event(Event& _event)
{

}

void GameEndOverlay::on_update()
{
    if (menu_button->mouse_release())
        app->event_callback(new InternalEvent(InternalEventType::CHANGE_START_MENU, 0));

    if (redo_button->mouse_release())
        app->event_callback(new InternalEvent(InternalEventType::CHANGE_START_GAME, 0));

    glm::mat4 view = app->get_window()->get_orthographic();

    message->draw(view);
    border->draw(view);

    menu_button->draw(view);
    redo_button->draw(view);
}
