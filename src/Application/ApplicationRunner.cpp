#include "ApplicationRunner.h"

ApplicationRunner::ApplicationRunner()
	: Runner(), m_running(true) {
	// Empty
}

ApplicationRunner::~ApplicationRunner()
{	// Clean up memory
	delete configuration.window;
	glfwTerminate();
}

void ApplicationRunner::on_event(Event& _event)
{
	get_state()->on_event(_event);
}

bool ApplicationRunner::initialize()
{	// For application initialization
	std::cout << "Initializing Application" << std::endl;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	configuration.window = Window::create_window(800, 600, "Test Window", NULL, NULL);
	if (!configuration.window) {
		std::cout << "Failed to create window" << std::endl;
		return false;
	}

	configuration.window->make_current_context();

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}

	// Hook event system
	std::function<void(Event& _event)> event_callback = std::bind(&ApplicationRunner::on_event, this, std::placeholders::_1);
	configuration.window->set_event_callback(event_callback);

	set_event_hooks();
	return true;
}

void ApplicationRunner::set_event_hooks()
{	// Hook events to event system
	glfwSetKeyCallback(configuration.window->raw_pointer(), [](GLFWwindow* _window, int _key, int _scancode, int _action, int _mods) {
		WindowUserPointer* user_ptr = (WindowUserPointer*)glfwGetWindowUserPointer(_window);
		
		if (_action == GLFW_PRESS)
		{
			user_ptr->event_callback(KeyPressedEvent(static_cast<KeyCode>(_key), 0));
			return;
		}

		if (_action == GLFW_RELEASE)
		{
			user_ptr->event_callback(KeyReleasedEvent(static_cast<KeyCode>(_key)));
			return;
		}
	});
}

bool ApplicationRunner::is_running()
{	 // Check if application is running
	return m_running;
}

void ApplicationRunner::internal_execute()
{	// Internally execute, distribute events
	// and update window buffer
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glfwSwapBuffers(configuration.window->raw_pointer());
	glfwPollEvents();

	if (glfwWindowShouldClose(configuration.window->raw_pointer()))
		terminate();
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