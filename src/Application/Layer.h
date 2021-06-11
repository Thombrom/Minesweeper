#pragma once

#include "Event/Event.h"

/*
	Interface for layers
*/
class LayerStack;
class Application;

class Layer
{
	friend class LayerStack;
public:
	virtual void on_update() = 0;
	virtual void on_event(Event& _event) = 0;

	virtual void on_push() = 0;
	virtual void on_pop() = 0;

	uint32_t get_position() { return position; }

protected:
	Layer(Application* _app, uint32_t _position = 0)
		: position(_position), app(_app) {};

	Application* app;

private:
	uint32_t position;
};

