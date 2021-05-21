#include "GameState.h"

GameState::GameState(ApplicationRunner* _runner, uint32_t _size_x, uint32_t _size_y, uint32_t _mine_count)
	: ApplicationState(_runner), size_x(_size_x), size_y(_size_y), mine_count(_mine_count)
{
	std::cout << "Game State Created" << std::endl;
	
	cursor_x = 0; cursor_y = 0;
	game.initialize(size_x, size_y, mine_count);

	draw_game();
}

void GameState::execute()
{
	
}

void GameState::update_state()
{
	if (game.get_state() == SweeperState::WON)
	{
		application->set_state(new GameWonState(application));
		return;
	}

	if (game.get_state() == SweeperState::LOST)
	{
		application->set_state(new GameLostState(application));
		return;
	}
}

void GameState::on_event(Event& _event)
{
	EventDispatcher dispatcher(_event);
	dispatcher.execute<KeyPressedEvent>(BIND_EVENT_FN(GameState::handle_key_pressed));
}

void GameState::handle_key_pressed(KeyPressedEvent& _event)
{
	if (_event.get_key_code() == KeyCode::Up)
	{
		cursor_y = clamp(cursor_y - 1, 0, size_y - 1);
		return draw_game();
	}

	if (_event.get_key_code() == KeyCode::Down)
	{
		cursor_y = clamp(cursor_y + 1, 0, size_y - 1);
		return draw_game();
	}

	if (_event.get_key_code() == KeyCode::Left)
	{
		cursor_x = clamp(cursor_x - 1, 0, size_x - 1);
		return draw_game();
	}

	if (_event.get_key_code() == KeyCode::Right)
	{
		cursor_x = clamp(cursor_x + 1, 0, size_x - 1);
		return draw_game();
	}

	if (_event.get_key_code() == KeyCode::Enter)
	{
		game.reveal(cursor_x, cursor_y);
		return draw_game();
	}
}



void GameState::draw_game()
{
	// Clear screen
	clear_screen();
	game.draw();

	// Draw cursor
	set_cursor(cursor_x, cursor_y);
	std::cout << "X" << std::endl;
}

uint32_t GameState::clamp(uint32_t _value, uint32_t _min, uint32_t _max)
{
	if (_value < _min && _value < _max)
		return _min;

	if (_value > _min && _value < _max)
		return _value;

	if (_value > _min && _value > _max)
		return _max;
}