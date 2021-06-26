#pragma once

#include <glad/glad.h>
#include <iostream>

#include "EventStack.h"
#include "LayerStack.h"
#include "Input.h"

#include "Platform/window.h"

/*
	The main thing that runs
	the application
*/
class Application
{
public:
	Application();
    ~Application();

	// General purpose
	void initialize();
	void event_callback(Event* _event);
	bool is_running() { return running; };
	void update();

	// Alter layers
	void push_layer(Layer* _layer) { layer_stack.push_layer(_layer); }
	void pop_layer() { layer_stack.pop_layer(); };
	void pop_after(uint32_t _position) { layer_stack.pop_after(_position); };

	// Window
	Window* get_window() { return window; }

	// Modifiying
	void  shutdown() { running = false; }
	void* get_data() { return m_data; }
	void  set_data(void* _data) { m_data = _data; }

private:
	Window* window;
	void* m_data;

	EventStack event_stack;
	LayerStack layer_stack;

	bool running;
};

#include "Layers/ApplicationLayer.h"
#include "Layers/MenuLayer.h"
#include "Layers/GameLayer.h"
#include "Layers/GameEndOverlay.h"
