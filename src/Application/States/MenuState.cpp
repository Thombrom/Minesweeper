#include "MenuState.h"

#include <iostream>

MenuState::MenuState(ApplicationRunner* _runner)
	: ApplicationState(_runner)
{
	std::cout << "Initialized menu state" << std::endl;
}

void MenuState::execute()
{

}

void MenuState::update_state()
{

}

void MenuState::on_event(Event& _event)
{
	EventDispatcher dispatcher(_event);
	dispatcher.execute<KeyboardKeyEvent>([](Event& _event)->void {
		std::cout << "Executing Key Event" << std::endl;
	});
}