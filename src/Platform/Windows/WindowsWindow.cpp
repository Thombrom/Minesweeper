#include "WindowsWindow.h"

bool WindowsWindow::s_GLFWinitialized = false;

Window* Window::create_window(const WindowProperties& _props)
{
	return new WindowsWindow(_props);
}

bool WindowsWindow::init_glfw()
{
	if (!s_GLFWinitialized)
	{
		int success = glfwInit();
		if (!success)
			return false;

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		
	}
	return true;
}

bool WindowsWindow::init_glad()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

WindowsWindow::WindowsWindow(const WindowProperties& _props)
	: properties(_props) {
	std::cout << "Created WindowsWindow" << std::endl;

	if (!init_glfw())
		__debugbreak();

	m_window = glfwCreateWindow((int)properties.width, (int)properties.height, properties.name.c_str(), nullptr, nullptr);
	glfwMakeContextCurrent(m_window);
	glfwSetWindowUserPointer(m_window, &properties);

	if (!init_glad())
		__debugbreak();

	hook_events();
}

WindowsWindow::~WindowsWindow()
{
	glfwDestroyWindow(m_window);
}

void WindowsWindow::hook_events()
{
	glfwSetKeyCallback(m_window, [](GLFWwindow* _window, int _key, int _scancode, int _action, int _mods) {
		WindowProperties* props = (WindowProperties*)glfwGetWindowUserPointer(_window);

		if (_action == GLFW_PRESS)
		{
			props->event_callback(new KeyPressedEvent(static_cast<KeyCode>(_key), 0));
			return;
		}

		if (_action == GLFW_RELEASE)
		{
			props->event_callback(new KeyReleasedEvent(static_cast<KeyCode>(_key)));
			return;
		}
	});
}

void WindowsWindow::update()
{
	glfwPollEvents();
	glfwSwapBuffers(m_window);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

uint32_t WindowsWindow::get_height() const
{ 
	return properties.height;
}

uint32_t WindowsWindow::get_width() const
{
	return properties.width;
}

void WindowsWindow::set_event_callback(const EventCallbackFn& _callback)
{
	properties.event_callback = _callback;
}
