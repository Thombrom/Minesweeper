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
	
	void initialize();
	void event_callback(Event* _event);
	bool is_running() { return running; }
	void update();

private:
	Window* window;

	EventStack event_stack;
	LayerStack layer_stack;

private:
	bool running;
};