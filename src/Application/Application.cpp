#include "Application.h"

Application::Application()
	: running(true) {
	// Empty
}

Application::~Application()
{
	ShaderLibrary::Destroy();
	FontLibrary::Destroy();
    delete window;
}

void Application::initialize()
{
	std::cout << "Initializing Application" << std::endl;
	window = Window::create_window(WindowProperties("Minesweeper", 1280, 720));
    window->set_clear_color(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

	// Set event callback
	std::function<void(Event* _event)> event_callback = std::bind(&Application::event_callback, this, std::placeholders::_1);
	window->set_event_callback(event_callback);
	
    // Initialize Libraries
    ShaderLibrary::Initialize();
    FontLibrary::Initialize();

    // Seed RNG
    srand(time(NULL));
}

void Application::event_callback(Event* _event)
{
	// React to certain functions internally
	EventDispatcher dispatcher(*_event);
	dispatcher.execute<WindowCloseEvent>([this](Event& _event)->bool {
		running = false;
		return false;
	});

	dispatcher.execute<InternalEvent>([this](InternalEvent& _event)->bool {
		std::cout << "Regisetered Internal Event" << std::endl;
		return false;
	});

	event_stack.push_event(_event);
	Input::RecordEvent(*_event);
}

void Application::update()
{
	for (Event* e : event_stack)
		layer_stack.stack_event_propagate(*e);

	layer_stack.stack_update();
	event_stack.swap_buffer();
	window->update();
}
