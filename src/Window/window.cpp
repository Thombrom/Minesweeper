#include "window.h"

Window::Window()
{
	// Empty
}

Window* Window::create_window(int _width, int _height, const char* _name, GLFWmonitor* _monitor, GLFWwindow* _share)
{	// Wrapper around creating the window
	Window* window = new Window();
	window->m_window = glfwCreateWindow(_width, _height, _name, _monitor, _share);
	if (!window)
		std::cout << "Failed to create GLFW window" << std::endl;

	// Set user pointer
	glfwSetWindowUserPointer(window->m_window, &(window->user_pointer));

	return window;
}