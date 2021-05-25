#pragma once

#include <vector>

#include "Event/Event.h"

/*
	A stack for holding events
	
	 - This implements two event buffers
	   which can be polled and swapped and
	   an itterator to go through the events
*/

class EventStack
{
public:
	EventStack();

	void push_event(Event* _event);
	void swap_buffer();

	std::vector<Event*>::iterator begin();
	std::vector<Event*>::iterator end();

private:
	inline std::vector<Event*>& get_active()   { return active ? stack_one : stack_two; }
	inline std::vector<Event*>& get_inactive() { return active ? stack_two : stack_one; }

private:
	std::vector<Event*> stack_one;
	std::vector<Event*> stack_two;

	bool active;
};