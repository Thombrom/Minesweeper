#pragma once
#include <windows.h>

#include "../ApplicationRunner.h"

class GameState : public ApplicationState
{
public:
	GameState(ApplicationRunner* _runner);

	void update_state();
	void execute();
	void on_event(Event& _event);

private:
	void handle_key_pressed(KeyPressedEvent& _event);
};