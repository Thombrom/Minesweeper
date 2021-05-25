#pragma once
/*

#include <windows.h>

#include "../ApplicationRunner.h"
#include "Game/Minesweeper.h"

class GameState : public ApplicationState
{
public:
	GameState(ApplicationRunner* _runner, uint32_t _size_x, uint32_t _size_y, uint32_t _mine_count);

	void update_state();
	void execute();
	void on_event(Event* _event);

private:
	void handle_key_pressed(KeyPressedEvent& _event);

	void draw_game();
	uint32_t clamp(uint32_t _value, uint32_t _min, uint32_t _max);
	

private:
	uint32_t size_x;
	uint32_t size_y;
	uint32_t mine_count;

	MineSweeper game;

	uint32_t cursor_x, cursor_y;
};

*/