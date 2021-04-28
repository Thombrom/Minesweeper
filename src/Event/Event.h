#pragma once
#include <iostream>

/*
	Enum for the different event types
*/
enum EventType
{
	KeyboardKeyEventType
};

/*
	Class for events

	Events should derive from this class
	and all nessecary information about
	that event should be in the derived
	class
*/
class Event
{
public:
	Event() 
	{
		std::cout << "Event Created" << std::endl;
	}

	virtual EventType get_event_type() = 0;
};

/*
	Class for dispatching events

	Allows you to create a dispatcher
	with that given event and call the 
	execute<EventType>(callback) to 
	execute the callback if the event 
	and type matches.
*/
class EventDispatcher
{
public:
	EventDispatcher(Event& _event)
		: m_event(&_event) {};

	template<typename EventClass>
	bool execute(void(*_function)(Event& _event)) {
		if (m_event->get_event_type() == EventClass::Type)
		{
			_function(*m_event);
			return true;
		}
		return false;
	}

protected:
	Event* m_event;
};

#include "KeyboardKeyEvent.h"