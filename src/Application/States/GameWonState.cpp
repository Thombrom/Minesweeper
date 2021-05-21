#include "GameWonState.h"

GameWonState::GameWonState(ApplicationRunner* _application)
	: ApplicationState(_application)
{
	clear_screen();
	std::cout << "You Won the game!" << std::endl;
}

void GameWonState::update_state()
{

}

void GameWonState::execute()
{

}

void GameWonState::key_pressed_event(KeyPressedEvent& _event)
{
	if (_event.get_key_code() == KeyCode::Enter)
		application->set_state(new MenuState(application));
}

void GameWonState::on_event(Event& _event)
{
	EventDispatcher dispatcher(_event);
	dispatcher.execute<KeyPressedEvent>(BIND_EVENT_FN(GameWonState::key_pressed_event));
}