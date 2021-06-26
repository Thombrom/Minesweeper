#include "GameLayer.h"

GameLayer::GameLayer(Application* _app, uint32_t _position)
	: Layer(_app, _position){
	std::cout << "GameLayer Constructed" << std::endl;

	// Retrieve appdata
	ApplicationData* appdata = (ApplicationData*)app->get_data();
	game.initialize(appdata->game_size_x, appdata->game_size_y, appdata->game_mine_count);

	// Initialize button
	back_button = TextButton{
		BorderRect::Create(glm::vec3(300.0f, -300.0f, 0.0f), glm::vec2(200.0f, 80.0f)),
		Text::Create("Menu", FontType::ARIAL),
	};

	back_button.text->set_center(glm::vec3(400.0f, -260.0f, 0.01f));
	back_button.rect->set_inside_color(glm::vec3(0.0f, 0.0f, 0.0f));
	back_button.rect->set_border_color(glm::vec3(0.0f, 1.0f, 0.0f));
	back_button.text->set_color(glm::vec3(0.0f, 1.0f, 0.0f));

	// Initialize game graphics
	game_tiles = TilePanel::Create(glm::vec2(appdata->game_size_x, appdata->game_size_y), game.get_values(), game.get_reveal());
	game_tiles->set_view(glm::vec3(-498.0f, -198.0f, 0.01f), glm::vec2(996.0f, 496.0f));

	game_frame = BorderRect::Create(glm::vec3(-500.0f, -200.0f, 0.0f), glm::vec2(1000.0f, 500.0f), 2);
	game_frame->set_inside_color(glm::vec3(0.0f, 0.0f, 0.0f));
	game_frame->set_border_color(glm::vec3(0.0f, 1.0f, 0.0f));
}

GameLayer::~GameLayer()
{

}

void GameLayer::on_pop() 
{
	std::cout << "GameLayer Popped" << std::endl;
	BorderRect::Destroy(back_button.rect);
	Text::Destroy(back_button.text);
}

void GameLayer::on_push()
{
	std::cout << "GameLayer Pushed" << std::endl;
}

void GameLayer::on_event(Event& _event)
{
	EventDispatcher dispatcher(_event);
    dispatcher.execute<WindowResizeEvent>([this](WindowResizeEvent& e)->bool {
        game_tiles->set_view(glm::vec3(-498.0f, -198.0f, 0.01f), glm::vec2(996.0f, 496.0f));
        return false;
    });

    // Perform event on game tiles
    float x = Input::MousePosX();
    float y = Input::MousePosY();
    if (x > -498.0f && x < -498.0f + 996.0f && y > -198.0f && y < -198.0f + 496.0f)
    {
        dispatcher.execute<MouseButtonPressedEvent>([this](MouseButtonPressedEvent& e)->bool {
            glm::vec2 mouse_pos = glm::vec2(Input::MousePosX(), Input::MousePosY());
            int res = pixelpos_to_tilepos(mouse_pos);

            if (res == -1)
                return false;

            uint32_t pos_x = res % game.get_size_x();
            uint32_t pos_y = (res - pos_x) / game.get_size_y();

            if (e.get_mouse_code() == MouseCode::Button1 && game.get_reveal_state(pos_x, pos_y) != 2)
            {
                std::cout << "Button 1 Pressed on " << res << std::endl;
                game.mark(pos_x, pos_y);
            }

            if (e.get_mouse_code() == MouseCode::Button0 && game.get_reveal_state(pos_x, pos_y) == 0)
            {
                std::cout << "Button 0 Pressed on " << res << std::endl;
                game.reveal(pos_x, pos_y);
            }

            game_tiles->reload_state();
            return true;
        });
    }
}

void GameLayer::on_update()
{

	// Button Hover Functionality
	if (back_button.rect->mouse_inside()) {
		back_button.rect->set_inside_color(glm::vec3(0.0f, 1.0f, 0.0f));
		back_button.text->set_color(glm::vec3(0.0f, 0.0f, 0.0f));
	}
	else {
		back_button.rect->set_inside_color(glm::vec3(0.0f, 0.0f, 0.0f));
		back_button.text->set_color(glm::vec3(0.0f, 1.0f, 0.0f));
	}

	// Button press functionality
	if (back_button.rect->mouse_release())
		app->event_callback(new InternalEvent(InternalEventType::CHANGE_START_MENU, 0));

	glm::mat4 view = app->get_window()->get_orthographic();
	back_button.rect->draw(view);
	back_button.text->draw(view);
    game_frame->draw(view);


    // Draw Tiles
    glm::mat4 trans = glm::mat4(1);
    trans = glm::translate(trans, glm::vec3(0, 0, 0));
	game_tiles->draw(trans);
}

int GameLayer::pixelpos_to_tilepos(glm::vec2 _pos) {
	ApplicationData* appdata = (ApplicationData*)app->get_data();
    glm::vec2 board_size = glm::vec2(appdata->game_size_x, appdata->game_size_y);
    float yoffset = 50;

    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(26 * board_size.x, 26 * board_size.y, 0.0f));
    transform = glm::translate(transform, glm::vec3(0.0f, -1 * yoffset, 0.0f));
    glm::vec4 new_pos = transform * glm::vec4(_pos.x, _pos.y, 0.0f, 1.0f);

    // Check bounds
    if (new_pos.x < 0 || new_pos.x > board_size.x * 52 || new_pos.y < 0 || new_pos.y > board_size.y * 52)
        return -1;

    return std::floor(new_pos.x / 52) + board_size.x * std::floor(new_pos.y / 52);
}
