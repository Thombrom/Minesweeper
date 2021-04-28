#pragma once
/*
	State responsible for displaying menu
	and letting you choose what you want to
	do - this is also the first state served
	to you when you launch the appliation
*/

#include "../ApplicationRunner.h"

class MenuState : public ApplicationState
{	
public:
	MenuState(ApplicationRunner* _runner);

	void on_event(Event& _event);

	void update_state();
	void execute();
};