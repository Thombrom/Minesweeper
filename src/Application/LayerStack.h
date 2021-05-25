#pragma once

#include <vector>

#include "Layer.h"

class LayerStack
{
public:
	typedef Layer* LayerPtr;

public:
	void push_layer(LayerPtr _layer);
	
	void pop_layer();
	void pop_layer(uint32_t _priority);
	void pop_layer_all(uint32_t _priority);

	void stack_update();
	void stack_event_propagate(Event& _event);

private:
	std::vector<LayerPtr> layer_stack;
};