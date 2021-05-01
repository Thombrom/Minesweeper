#include "Minesweeper.h"

MineSweeper::MineSweeper()
{

}

MineSweeper::~MineSweeper()
{
	free(board_values);
	free(board_revelations);
}

void MineSweeper::initialize(uint32_t _size_x, uint32_t _size_y, uint32_t _mine_count)
{	// Initialize values
	size_x		= _size_x;
	size_y		= _size_y;
	num_mines	= _mine_count;

	// If we want to combine these we could use high bit as revealed
	// but we are not in the old age of computers and memory is not an issue 
	size_t board_size = _size_x * _size_y * sizeof(uint8_t);
	board_values	  = (uint8_t*)malloc(board_size);
	board_revelations = (uint8_t*)malloc(board_size);

	memset(board_values, 0, board_size);
	memset(board_revelations, 0, board_size);
	distribute_mines();
}

void MineSweeper::reveal(uint32_t _x, uint32_t _y)
{
	if (_x >= size_x || _y >= size_y || board_revelations[_y * size_x + _x])
		return;	// Out of bounds

	board_revelations[_y * size_x + _x] = 1;
	uint8_t value = board_values[_y * size_x + _x];

	if (value != 0)	// i.e blank
		return;

	// Reveal squares in a circle around
	reveal(_x - 1, _y - 1); reveal(_x - 1, _y + 0); reveal(_x - 1, _y + 1);
	reveal(_x + 0, _y - 1); reveal(_x + 0, _y + 0); reveal(_x + 0, _y + 1);
	reveal(_x + 1, _y - 1); reveal(_x + 1, _y + 0); reveal(_x + 1, _y + 1);
}

void MineSweeper::distribute_mines()
{
	if (num_mines > size_x * size_y)
		return;	// Failsave for infinite loop

	uint32_t remaining_mines = num_mines;
	while (num_mines > 0)
	{
		uint32_t x, y;
		x = rand() * size_x / RAND_MAX;
		y = rand() * size_y / RAND_MAX;

		if (board_values[y * size_x + x] != 10)
		{
			board_values[y * size_x + x] = 10;
			num_mines--;

			increase_cell(x - 1, y - 1); increase_cell(x - 1, y + 0); increase_cell(x - 1, y + 1);
			increase_cell(x + 0, y - 1); increase_cell(x + 0, y + 0); increase_cell(x + 0, y + 1);
			increase_cell(x + 1, y - 1); increase_cell(x + 1, y + 0); increase_cell(x + 1, y + 1);
		}
	}
}

void MineSweeper::increase_cell(uint32_t _x, uint32_t _y)
{
	if (_x >= size_x || _y >= size_y || board_values[_y * size_x + _x] == 10)
		return;

	board_values[_y * size_x + _x] += 1;
}

SweeperState MineSweeper::get_state()
{
	uint32_t uncovered = 0;

	// Check if mine revealed
	for (size_t itt = 0; itt < size_x * size_y; itt++)
	{
		if (board_revelations[itt] && board_values[itt] == 10)
			return SweeperState::LOST;

		if (!board_revelations[itt] && board_values[itt] < 10)
			uncovered++;
	}

	if (uncovered == 0)
		return SweeperState::WON;
	return SweeperState::ONGOING;
}

uint32_t MineSweeper::clamp(uint32_t _value, uint32_t _min, uint32_t _max)
{
	if (_value < _min)
		return _min;
	if (_value > _max)
		return _max;
	return _value;
}

void MineSweeper::draw()
{	// Draws the game
	for (size_t itt = 0; itt < size_x * size_y; itt++)
	{
		// If end of line
		if (itt && !(itt % size_x))
			std::cout << std::endl;

		// If board is 10 = mine
		if (board_revelations[itt] && board_values[itt] == 10)
			std::cout << "x";

		if (board_revelations[itt] && board_values[itt] < 10)
			std::cout << (int)board_values[itt];
		
		if (!board_revelations[itt])
			std::cout << "_";
	}
}
