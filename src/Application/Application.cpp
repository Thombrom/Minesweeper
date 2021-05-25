#include "Application.h"

Application::Application()
	: running(true) {
	// Empty
}

void Application::initialize()
{
	std::cout << "Initializing Application" << std::endl;
	window = Window::create_window(WindowProperties("Minesweeper", 1280, 720));

	// Set event callback
	std::function<void(Event* _event)> event_callback = std::bind(&Application::event_callback, this, std::placeholders::_1);
	window->set_event_callback(event_callback);
}

void Application::event_callback(Event* _event)
{
	std::cout << "Event pushed to stack" << std::endl;
	event_stack.push_event(_event);
}

void Application::update()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	for (Event* e : event_stack)
		layer_stack.stack_event_propagate(*e);

	event_stack.swap_buffer();
	window->update();
}