#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "../window.h"

class WindowsWindow : public Window
{
public:
	WindowsWindow(const WindowProperties& _properties);
	~WindowsWindow();

	void update() override;

	uint32_t get_width() const override;
	uint32_t get_height() const override;

	void set_event_callback(const EventCallbackFn& _callback) override;

private:
	bool init_glfw();
	bool init_glad();
	
	void hook_events();

private:
	GLFWwindow* m_window;

	WindowProperties properties;
	static bool s_GLFWinitialized;
};