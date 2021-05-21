#pragma once

/*
	State responsible for
	conveying the message
	that the player won the game
*/

#include "../ApplicationRunner.h"

class GameWonState : public ApplicationState
{
public:
	GameWonState(ApplicationRunner* _application);

	void update_state();
	void execute();
	void on_event(Event& _event);

private:
	void key_pressed_event(KeyPressedEvent& _event);
};