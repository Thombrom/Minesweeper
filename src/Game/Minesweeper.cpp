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
    distributed = false;

	// If we want to combine these we could use high bit as revealed
	// but we are not in the old age of computers and memory is not an issue 
	size_t board_size = _size_x * _size_y * sizeof(uint8_t);
	board_values	  = (uint8_t*)malloc(board_size);
	board_revelations = (uint8_t*)malloc(board_size);

	memset(board_values, 0, board_size);
	memset(board_revelations, 0, board_size);
}

void MineSweeper::reveal(uint32_t _x, uint32_t _y)
{
	if (_x >= size_x || _y >= size_y || board_revelations[_y * size_x + _x])
		return;	// Out of bounds

	board_revelations[_y * size_x + _x] = 2;
	uint8_t value = board_values[_y * size_x + _x];

	if (value != 0)	// i.e blank
		return;

	// Reveal squares in a circle around
	reveal(_x - 1, _y - 1); reveal(_x - 1, _y + 0); reveal(_x - 1, _y + 1);
	reveal(_x + 0, _y - 1); reveal(_x + 0, _y + 0); reveal(_x + 0, _y + 1);
	reveal(_x + 1, _y - 1); reveal(_x + 1, _y + 0); reveal(_x + 1, _y + 1);
}

void MineSweeper::splash_reveal(uint32_t _x, uint32_t _y) 
{
	if (_x >= size_x || _y >= size_y)
		return;	// Out of bounds

    if (board_revelations[_y * size_x + _x] != 2)
        return; // Not revealed

    // Check that it has been correctly marked
    uint32_t markings = 0;
    for (int ittx = -1; ittx <= 1; ittx++) {
        for (int itty = -1; itty <= 1; itty++) {
            uint32_t nx = _x + ittx;
            uint32_t ny = _y + itty;

            if (nx >= size_x || ny >= size_y)
                continue;   // Not on board

            if (board_revelations[ny * size_x + nx] == 1)
                markings++;
        }
    }

    if (markings != board_values[_y * size_x + _x])
        return; // Invalid marking, we abort

    // We reveal all surrounding mines
	reveal(_x - 1, _y - 1); reveal(_x - 1, _y + 0); reveal(_x - 1, _y + 1);
	reveal(_x + 0, _y - 1); reveal(_x + 0, _y + 0); reveal(_x + 0, _y + 1);
	reveal(_x + 1, _y - 1); reveal(_x + 1, _y + 0); reveal(_x + 1, _y + 1);
}

void MineSweeper::mark(uint32_t _x, uint32_t _y) {
    uint8_t* pos = board_revelations + _y * size_x + _x;
    *pos = *pos == 1 ? 0 : 1;
}

void MineSweeper::distribute_mines(uint32_t _x, uint32_t _y)
{
	if (num_mines > size_x * size_y - 9)
		return;	// Failsave for infinite loop

	uint32_t remaining_mines = num_mines;
	while (remaining_mines > 0)
	{
		uint32_t x, y;
		x = (float)rand() / RAND_MAX * size_x;
		y = (float)rand() / RAND_MAX * size_y;

		if (board_values[y * size_x + x] != 10
            && !(y <= (_y + 1) && y >=  (_y - 1) && x <= (_x + 1) && x >= (_x - 1)))
		{
			board_values[y * size_x + x] = 10;
			remaining_mines--;

			increase_cell(x - 1, y - 1); increase_cell(x - 1, y + 0); increase_cell(x - 1, y + 1);
			increase_cell(x + 0, y - 1); increase_cell(x + 0, y + 0); increase_cell(x + 0, y + 1);
			increase_cell(x + 1, y - 1); increase_cell(x + 1, y + 0); increase_cell(x + 1, y + 1);
		}
	}

    distributed = true;
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
    uint32_t marked = 0;

	// Check if mine revealed
	for (size_t itt = 0; itt < size_x * size_y; itt++)
	{
		if (board_revelations[itt] == 2 && board_values[itt] == 10)
			return SweeperState::LOST;

        if (board_revelations[itt] == 1 && board_values[itt] == 10)
            marked++;

		if (board_revelations[itt] != 2 && board_values[itt] < 10)
			uncovered++;
	}

    if (marked == num_mines)
        return SweeperState::WON;

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

int32_t MineSweeper::mines_left()
{
    int32_t mines_left = num_mines;
    for (size_t itt = 0; itt < size_x * size_y; itt++)
    {
        if (board_revelations[itt] == 1)
            mines_left -= 1;
    }

    return mines_left;
}
