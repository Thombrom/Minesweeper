#pragma once

/*
	State responsible for
	conveying the sad message
	that the player lost the game
*/

#include "../ApplicationRunner.h"

class GameLostState : public ApplicationState
{
public:
	GameLostState(ApplicationRunner* _application);

	void update_state();
	void execute();
	void on_event(Event& _event);

private:
	void key_pressed_event(KeyPressedEvent& _event);
};