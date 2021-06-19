#include "GameLayer.h"

GameLayer::GameLayer(Application* _app, uint32_t _position)
	: Layer(_app, _position){
	std::cout << "GameLayer Constructed" << std::endl;

	// Retrieve appdata
	ApplicationData* appdata = (ApplicationData*)app->get_data();
	game.initialize(appdata->game_size_x, appdata->game_size_y, appdata->game_mine_count);

	// Initialize button
	back_button = Button::Create(glm::vec3(200, -200, 0), glm::vec2(200, 80), "Menu");
	back_button->set_button_color(glm::vec3(0.0f, 0.0f, 0.0f));
	back_button->set_border_color(glm::vec3(0.0f, 1.0f, 0.0f));
	back_button->set_text_color(glm::vec3(0.0f, 1.0f, 0.0f));
}

GameLayer::~GameLayer()
{

}

void GameLayer::on_pop() 
{
	std::cout << "GameLayer Popped" << std::endl;
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
	if (back_button->mouse_inside()) {
		back_button->set_button_color(glm::vec3(0.0f, 1.0f, 0.0f));
		back_button->set_text_color(glm::vec3(0.0f, 0.0f, 0.0f));
	}
	else {
		back_button->set_button_color(glm::vec3(0.0f, 0.0f, 0.0f));
		back_button->set_text_color(glm::vec3(0.0f, 1.0f, 0.0f));
	}

	// Button press functionality
	if (back_button->mouse_release())
		app->event_callback(new InternalEvent(InternalEventType::CHANGE_START_MENU, 0));

	back_button->draw(app->get_window()->get_orthographic());
}