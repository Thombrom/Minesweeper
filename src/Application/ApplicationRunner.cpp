#include "ApplicationRunner.h"

ApplicationRunner::ApplicationRunner()
	: Runner(), m_running(true) {
	// Empty
}

ApplicationRunner::~ApplicationRunner()
{	// Clean up memory
	delete configuration.window;
}

void ApplicationRunner::on_event(Event& _event)
{
	get_state()->on_event(_event);
}

bool ApplicationRunner::initialize()
{	// For application initialization
	std::cout << "Initializing Application" << std::endl;
	configuration.window = Window::create_window(WindowProperties("MineSweeper", 1280, 720));

	// Hook event system
	std::function<void(Event& _event)> event_callback = std::bind(&ApplicationRunner::on_event, this, std::placeholders::_1);
	configuration.window->set_event_callback(event_callback);

	// Other setups
	srand(time(NULL));

	return true;
}

void ApplicationRunner::set_event_hooks()
{	// Hook events to event system
	
}

bool ApplicationRunner::is_running()
{	 // Check if application is running
	return m_running;
}

void ApplicationRunner::internal_execute_before()
{	// Internally execute, distribute events
	// and update window buffer
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void ApplicationRunner::internal_execute_after()
{
	configuration.window->update();
}

ApplicationState* ApplicationRunner::get_state()
{
	return (ApplicationState*)m_state;
}

void ApplicationRunner::terminate()
{	// For terminating the application
	m_running = false;
}

ApplicationState::ApplicationState(ApplicationRunner* _runner)
	: RunState(_runner) {
	application = _runner;
}

void ApplicationState::clear_screen()
{
	// Clear screen
	// https://stackoverflow.com/questions/6486289/how-can-i-clear-console
	COORD topLeft = { 0, 0 };
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen;
	DWORD written;

	GetConsoleScreenBufferInfo(console, &screen);
	FillConsoleOutputCharacterA(
		console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	FillConsoleOutputAttribute(
		console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
		screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	SetConsoleCursorPosition(console, topLeft);
}

void ApplicationState::set_cursor(uint32_t _x, uint32_t _y)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen;

	GetConsoleScreenBufferInfo(console, &screen);
	if (_x >= screen.dwSize.X || _y >= screen.dwSize.Y)
		return;	// Don't draw outside buffer

	SetConsoleCursorPosition(console, COORD{ (SHORT)_x, (SHORT)_y });
}