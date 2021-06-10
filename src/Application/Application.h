#pragma once

#include <glad/glad.h>
#include <iostream>

#include "EventStack.h"
#include "LayerStack.h"

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
	bool is_running() { return running; }
	void update();

	// Alter layers
	void push_layer(Layer* _layer) { layer_stack.push_layer(_layer); }
	void pop_layer() { layer_stack.pop_layer(); };
	void pop_layer(uint32_t _position) { layer_stack.pop_layer(_position); };
	void pop_layer_all(uint32_t _position) { layer_stack.pop_layer_all(_position); };

	// Window
	Window* get_window() { return window; }

private:
	Window* window;

	EventStack event_stack;
	LayerStack layer_stack;

	bool running;
};

#include "Layers/ApplicationLayer.h"
