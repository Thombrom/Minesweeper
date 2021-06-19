#pragma once

#include <vector>
#include <memory>

#include "Layer.h"

class LayerStack
{
public:
	typedef Layer* LayerPtr;

public:
	LayerStack();
	~LayerStack() { std::cout << "This layerstack is getting deleted" << std::endl; }

	void push_layer(LayerPtr _layer);
	void pop_layer();
	void pop_after(uint32_t _position);
	
	void stack_update();
	void stack_event_propagate(Event& _event);

private:
	struct Node
	{
		Node* m_next;
		Node* m_before;

		LayerPtr m_layer;
	};

	Node* m_root;
};