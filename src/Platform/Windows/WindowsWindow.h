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

    void set_clear_color(const glm::vec4& _clear_color) override { clear_color = _clear_color; }

private:
	bool init_glfw();
	bool init_glad();
	
	void hook_events();

private:
	GLFWwindow* m_window;

	WindowProperties properties;
	static bool s_GLFWinitialized;

private:
    glm::vec4 clear_color;
};
