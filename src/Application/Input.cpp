#include "Input.h"

/*
 *  For static variables only
 */
bool Input::key_state[350] = { false };

uint32_t Input::window_height;
uint32_t Input::window_width;
float Input::cursor_pos_x;
float Input::cursor_pos_y;