#pragma once

/*
	Minesweeper implementation

	This will hold the board, handle the creation
	and the revelation of the mines and such. It will
	essentially be the container for everything that
	has to do with the game aspect of it
*/

#include <stdint.h>
#include <stdlib.h>
#include <cstring>
#include <iostream>

enum class SweeperState
{
	WON, LOST, ONGOING
};

class MineSweeper
{
public:
	MineSweeper();
	~MineSweeper();

	void initialize(uint32_t _size_x, uint32_t _size_y, uint32_t _mine_count);
	void distribute_mines(uint32_t _x, uint32_t _y);
	void draw();

	void reveal(uint32_t _x, uint32_t _y);
    void splash_reveal(uint32_t _x, uint32_t _y);
    void mark(uint32_t _x, uint32_t _y);
    uint8_t get_reveal_state(uint32_t _x, uint32_t _y) { return board_revelations[_y * size_x + _x]; }
	SweeperState get_state();

	uint8_t* get_values() { return board_values; }
	uint8_t* get_reveal() { return board_revelations; }

    uint32_t get_size_x() { return size_x; }
    uint32_t get_size_y() { return size_y; }
    bool mines_distributed() { return distributed; }
    int32_t  mines_left();

private:
	uint32_t clamp(uint32_t _value, uint32_t _min, uint32_t _max);
	void increase_cell(uint32_t _x, uint32_t _y);

private:
	// Game board and revelations
	uint32_t size_x;
	uint32_t size_y;
	uint32_t num_mines;
    bool distributed;

	uint8_t* board_values;
	uint8_t* board_revelations;
};
