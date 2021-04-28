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
	dispatcher.execute<KeyPressedEvent>(std::bind(&GameState::handle_key_pressed, this, std::placeholders::_1));
}

void GameState::handle_key_pressed(KeyPressedEvent& _event)
{
	std::cout << "Key Pressed: " << _event.get_key_code() << std::endl;
}