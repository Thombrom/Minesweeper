#include "EventStack.h"

EventStack::EventStack()
{
	active = true;
}

void EventStack::push_event(Event* _event)
{
	get_inactive().emplace_back(_event);
}

void EventStack::swap_buffer()
{
	// Swap buffers
	active = !active;

	// Delete and flush
	// inactive

	for (Event* e : get_inactive())
		delete e;
	get_inactive().clear();
}

std::vector<Event*>::iterator EventStack::begin()
{
	return get_active().begin();
}

std::vector<Event*>::iterator EventStack::end()
{
	return get_active().end();
}