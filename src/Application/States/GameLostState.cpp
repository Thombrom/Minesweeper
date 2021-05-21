#include "GameLostState.h"

GameLostState::GameLostState(ApplicationRunner* _application)
	: ApplicationState(_application)
{
	clear_screen();
	std::cout << "You Lost the game!" << std::endl;
}

void GameLostState::update_state()
{

}

void GameLostState::execute()
{

}

void GameLostState::key_pressed_event(KeyPressedEvent& _event)
{
	if (_event.get_key_code() == KeyCode::Enter)
		application->set_state(new MenuState(application));
}

void GameLostState::on_event(Event& _event)
{
	EventDispatcher dispatcher(_event);
	dispatcher.execute<KeyPressedEvent>(BIND_EVENT_FN(GameLostState::key_pressed_event));
}