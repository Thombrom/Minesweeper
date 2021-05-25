#pragma once
/*
	State responsible for displaying menu
	and letting you choose what you want to
	do - this is also the first state served
	to you when you launch the appliation
*/
/*
#include <string>
#include <iostream>
#include <windows.h>

#include "../ApplicationRunner.h"
#include "Render/Font.h"

class MenuState : public ApplicationState
{	
public:
	MenuState(ApplicationRunner* _runner);

	void on_event(Event* _event);
	void update_state();
	void execute();

private:
	void draw_menu();

	void handle_key_pressed(KeyPressedEvent& _event);

private:
	Font font;

	uint8_t menu_pos;
	std::string menu_items[3] = {
		"Play Game",
		"Statistics",
		"Exit",
	};

	enum class MenuItem {
		PLAY_GAME = 0,
		STATISTICS = 1,
		EXIT = 2
	};
};*/