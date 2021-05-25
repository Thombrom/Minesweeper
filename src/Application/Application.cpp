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
	// React to certain functions internally
	EventDispatcher dispatcher(*_event);
	dispatcher.execute<WindowCloseEvent>([this](Event& _event)->bool {
		running = false;
		return true;
	});

	
	event_stack.push_event(_event);
}

void Application::update()
{
	for (Event* e : event_stack)
		layer_stack.stack_event_propagate(*e);

	for (Layer* layer : layer_stack)
		layer->on_update();

	event_stack.swap_buffer();
	window->update();
}