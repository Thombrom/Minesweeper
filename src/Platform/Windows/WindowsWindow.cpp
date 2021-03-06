#include "WindowsWindow.h"

#if defined (MINESWEEPER_PLATFORM_WINDOWS)
    #define breakpoint __debugbreak()
#elif defined (MINESWEEPER_PLATFORM_LINUX)
    #define breakpoint exit(1)
#else
    #define breakpoint static_assert(false, "Only Windows and Linux Support")
#endif


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
    glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    return true;
}

WindowsWindow::WindowsWindow(const WindowProperties& _props)
	: properties(_props) {
	std::cout << "Created WindowsWindow" << std::endl;

	if (!init_glfw())
		breakpoint;

	m_window = glfwCreateWindow((int)properties.width, (int)properties.height, properties.name.c_str(), nullptr, nullptr);
	glfwMakeContextCurrent(m_window);
	glfwSetWindowUserPointer(m_window, &properties);

	if (!init_glad())
		breakpoint;

	hook_events();
	glViewport(0, 0, _props.width, _props.height);

    WindowResizeEvent initial_size_event = WindowResizeEvent(_props.width, _props.height);
	Input::RecordEvent(initial_size_event);

    // Default variable initialization
    clear_color = glm::vec4(0.2f, 0.3f, 0.3f, 1.0f);
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

		if (_action == GLFW_REPEAT)
		{
			props->event_callback(new KeyPressedEvent(static_cast<KeyCode>(_key), 1));
			return;
		}
	});


	glfwSetMouseButtonCallback(m_window, [](GLFWwindow* _window, int _key, int _action, int _mods) {
		WindowProperties* props = (WindowProperties*)glfwGetWindowUserPointer(_window);

		if (_action == GLFW_PRESS)
		{
			props->event_callback(new MouseButtonPressedEvent(static_cast<MouseCode>(_key)));
			return;
		}

		if (_action == GLFW_RELEASE)
		{
			props->event_callback(new MouseButtonReleasedEvent(static_cast<MouseCode>(_key)));
			return;
		}
	});

	glfwSetCursorPosCallback(m_window, [](GLFWwindow* _window, double _x, double _y) {
		WindowProperties* props = (WindowProperties*)glfwGetWindowUserPointer(_window);

        // Adjust window center to be (0, 0)
        double nx = _x - props->width / 2;
        double ny = props->height / 2 - _y;

		props->event_callback(new MouseMovedEvent(nx, ny));
	});

	glfwSetScrollCallback(m_window, [](GLFWwindow* _window, double _x, double _y) {
		WindowProperties* props = (WindowProperties*)glfwGetWindowUserPointer(_window);
		props->event_callback(new MouseScrollEvent(_x, _y));
	});

	glfwSetWindowPosCallback(m_window, [](GLFWwindow* _window, int _x, int _y) {
		WindowProperties* props = (WindowProperties*)glfwGetWindowUserPointer(_window);
		props->event_callback(new WindowMovedEvent(_x, _y));
	});

	glfwSetWindowSizeCallback(m_window, [](GLFWwindow* _window, int _x, int _y) {
		WindowProperties* props = (WindowProperties*)glfwGetWindowUserPointer(_window);

        props->width = _x;
        props->height = _y;

		props->event_callback(new WindowResizeEvent(_x, _y));
	});

	glfwSetWindowCloseCallback(m_window, [](GLFWwindow* _window) {
		WindowProperties* props = (WindowProperties*)glfwGetWindowUserPointer(_window);
		props->event_callback(new WindowCloseEvent());
	});

	glfwSetWindowFocusCallback(m_window, [](GLFWwindow* _window, int _action) {
		WindowProperties* props = (WindowProperties*)glfwGetWindowUserPointer(_window);

		if (_action == GLFW_TRUE)
		{
			props->event_callback(new WindowFocusEvent());
		}

		if (_action == GLFW_FALSE)
		{
			props->event_callback(new WindowLostFocusEvent());
		}
	});
}

void WindowsWindow::update()
{
	glfwPollEvents();
	glfwSwapBuffers(m_window);
	glClearColor(clear_color.r, clear_color.g, clear_color.b, clear_color.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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

glm::mat4 WindowsWindow::get_orthographic()
{
    float height, width;
    height = (float)properties.height;
    width  = (float)properties.width;

    return glm::ortho(width / -2, width / 2, height / -2, height / 2);
}
