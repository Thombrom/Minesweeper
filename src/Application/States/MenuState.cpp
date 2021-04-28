#include "MenuState.h"

#include <iostream>

MenuState::MenuState(ApplicationRunner* _runner)
	: ApplicationState(_runner)
{
	
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
	dispatcher.execute<KeyPressedEvent>([](Event& _event)->void {
		std::cout << "Executing Key Pressed Event" << std::endl;
	});

	dispatcher.execute<KeyReleasedEvent>([](Event& _event)->void {
		std::cout << "Executing Key Release Event" << std::endl;
	});
}