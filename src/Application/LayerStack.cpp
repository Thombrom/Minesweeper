#include "LayerStack.h"

LayerStack::LayerStack()
{
	// Initialize Root
	m_root = new Node();
}

void LayerStack::push_layer(LayerPtr _layer)
{
	uint32_t pos = 0;
	Node* cond = m_root;
	
	while (cond->m_next != nullptr)
	{
		cond = cond->m_next;
		pos += 1;
	}

	// Save pushed position
	_layer->position = pos;

	cond->m_next = new Node();
	cond->m_next->m_layer  = _layer;
	cond->m_next->m_before = cond;
}

void LayerStack::pop_layer()
{
	Node* cond = m_root;
	while (cond->m_next != nullptr && cond->m_next->m_next != nullptr)
		cond = cond->m_next;

	if (cond->m_next == nullptr)
	{
		// Do nothing, we don't have any layers
		return;
	}

	cond->m_next->m_layer->on_pop();
	delete cond->m_next->m_layer;
	delete cond->m_next;
	cond->m_next = nullptr;
}

void LayerStack::pop_after(uint32_t	_pos)
{
	uint32_t itt = -1;		// Root is -1
	Node* cond = m_root;
	Node* buffer;

	while (cond->m_next != nullptr && itt != _pos)
	{
		buffer = cond->m_next;
		if (itt == _pos - 1)
			cond->m_next = nullptr;

		cond = buffer;
		itt++;
	}

	if (itt != _pos)
		return;			// Did not reach specifed node

	
	while (cond != nullptr)
	{
		buffer = cond->m_next;
		cond->m_layer->on_pop();
		delete cond->m_layer;
		delete cond;
		cond = buffer;
	}
}

void LayerStack::stack_update()
{
	Node* cond = m_root->m_next;		// Root does not have layer
	while (cond != nullptr)
	{
		cond->m_layer->on_update();
		cond = cond->m_next;
	}
}

void LayerStack::stack_event_propagate(Event& _event)
{
	Node* cond = m_root;
	while (cond->m_next != nullptr)
		cond = cond->m_next;

	// We are now at the end
	while (cond->m_before != nullptr)
	{
		cond->m_layer->on_event(_event);
		cond = cond->m_before;
	}
}