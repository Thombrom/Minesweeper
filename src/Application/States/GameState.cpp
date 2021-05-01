#include "GameState.h"

GameState::GameState(ApplicationRunner* _runner)
	: ApplicationState(_runner)
{
	std::cout << "Game State Created" << std::endl;
}

void GameState::execute()
{
	
}

void GameState::update_state()
{

}

void GameState::on_event(Event& _event)
{
	EventDispatcher dispatcher(_event);
	//dispatcher.execute<KeyPressedEvent>(std::bind(&GameState::handle_key_pressed, this, std::placeholders::_1));
	dispatcher.execute<KeyPressedEvent>(BIND_EVENT_FN(GameState::handle_key_pressed));
}

void GameState::handle_key_pressed(KeyPressedEvent& _event)
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ 0, 0 });
	std::cout << "Key Pressed: " << _event.get_key_code() << std::endl;
	if (_event.get_key_code() == KeyCode::Up) {
		//application->setState(new MenuState(application));
		std::cout << "Pressed Up" << std::endl;
	}

	if (_event.get_key_code() == KeyCode::Down) {
		std::cout << "Pressed Down" << std::endl;
	}
}