#include "MenuState.h"
/*
MenuState::MenuState(ApplicationRunner* _runner)
	: ApplicationState(_runner)
{
	std::cout << "Welcome to the Minesweeper Game!" << std::endl;
	menu_pos = 0;
	
	//clear_screen();
	//draw_menu();

	// OPENGL TESTING
	font.load("resources/fonts/arial.ttf");
}

void MenuState::execute()
{
	// Honestly nothing here
	font.render_text("This is a test", 25.0f, 25.0f, 1.0f, glm::vec3(0.5f, 0.8f, 0.2f));
}

void MenuState::update_state()
{
	// Honestly nothing here
}

void MenuState::on_event(Event* _event)
{
	EventDispatcher dispatcher(*_event);
	dispatcher.execute<KeyPressedEvent>(BIND_EVENT_FN(MenuState::handle_key_pressed));
}

void MenuState::handle_key_pressed(KeyPressedEvent& _event)
{
	// Move item pointer one up
	if (_event.get_key_code() == KeyCode::Up) {
		menu_pos = (menu_pos - 1) % (sizeof(menu_items) / sizeof(std::string));
		//clear_screen();
		//draw_menu();
		return;
	}

	// Move item pointer one down
	if (_event.get_key_code() == KeyCode::Down) {
		menu_pos = (menu_pos + 1) % (sizeof(menu_items) / sizeof(std::string));
		//clear_screen();
		//draw_menu();
		return;
	}

	if (_event.get_key_code() == KeyCode::Enter)
	{
		// If on 'Play Game' go to game state
		if (menu_pos == static_cast<uint8_t>(MenuItem::PLAY_GAME))
		{
			application->set_state(new GameState(application, 10, 10, 10));
			return;
		}

		// Not yet implemented yet
		if (menu_pos == static_cast<uint8_t>(MenuItem::STATISTICS))
		{
			std::cout << "Not implemented yet" << std::endl;
			return;
		}

		// Terminate
		if (menu_pos == static_cast<uint8_t>(MenuItem::EXIT))
		{
			application->terminate();
			return;
		}
	}
}

void MenuState::draw_menu()
{
	// Draw menu
	for (uint8_t itt = 0; itt < sizeof(menu_items) / sizeof(std::string); itt++)
	{
		if (itt == menu_pos)
			std::cout << "-> ";
		std::cout << menu_items[itt] << std::endl;
	}
}
*/