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

	// Initialize game rect
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

	// Draw Button
	back_button.rect->draw(view);
	back_button.text->draw(view);

	// Draw Game Frame
	game_frame->draw(view);
}