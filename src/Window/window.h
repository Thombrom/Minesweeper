#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <functional>
#include <iostream>

#include "Event/Event.h"

// For the GLFWWindow
struct WindowUserPointer
{
	using EventCallbackFn = std::function<void(Event& _event)>;
	EventCallbackFn event_callback;

	WindowUserPointer(EventCallbackFn& _callback = std::function<void(Event&)>())
		: event_callback(_callback) {};
};

class Window
{
	using EventCallbackFn = std::function<void(Event& _event)>;
public:
	Window();
	static Window* create_window(int _width, int _height, const char* _name, GLFWmonitor* _monitor, GLFWwindow* _share);

	operator int() const { return m_window != NULL; }
	GLFWwindow* raw_pointer() { return m_window; }
	void make_current_context() { glfwMakeContextCurrent(m_window); }

	void set_event_callback(EventCallbackFn& _event_callback) { user_pointer.event_callback = _event_callback; };

private:
	WindowUserPointer user_pointer;
	GLFWwindow* m_window;
};