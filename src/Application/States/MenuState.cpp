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