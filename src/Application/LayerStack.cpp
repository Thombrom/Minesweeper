#include "LayerStack.h"

void LayerStack::push_layer(LayerPtr _layer)
{
	// Find switch between layer priority
	_layer->on_push();
	for (size_t itt = 0; itt < layer_stack.size(); itt++)
	{
		if (_layer->position < layer_stack.at(itt)->position) {
			layer_stack.insert(layer_stack.begin() + itt, _layer);
			return;
		}
	}

	// Otherwise put it in the back
	layer_stack.emplace_back(_layer);
}

void LayerStack::pop_layer()
{
	layer_stack.back()->on_pop();;
	layer_stack.pop_back();
}

void LayerStack::pop_layer(uint32_t _position)
{
	for (auto itt = layer_stack.rbegin(); itt != layer_stack.rend(); itt++)
	{
		if ((*itt)->position == _position)
		{
			(*itt)->on_pop();
			layer_stack.erase(itt.base());
			return;
		}
	}
}

void LayerStack::pop_layer_all(uint32_t _position)
{
	// Pops all layers of higher position than or equal priority
	for (auto itt = layer_stack.begin(); itt != layer_stack.end(); itt++)
	{
		if ((*itt)->position >= _position)
		{
			(*itt)->on_pop();
			layer_stack.erase(itt);
			return;
		}
	}
}

void LayerStack::stack_update()
{
	for (auto itt = layer_stack.begin(); itt != layer_stack.end(); itt++)
		(*itt)->on_update();

	
}

void LayerStack::stack_event_propagate(Event& _event)
{
	for (auto itt = layer_stack.rbegin(); itt != layer_stack.rend(); itt++)
		(*itt)->on_event(_event);
}

