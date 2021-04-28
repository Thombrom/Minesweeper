#pragma once
#include "Event.h"

class KeyboardKeyEvent : public Event
{
public:
	KeyboardKeyEvent()
		: Event()
	{
		std::cout << "KeyboardKeyEvent created" << std::endl;
	}
	
	EventType get_event_type() { return EventType::KeyboardKeyEventType; }
	static const EventType Type = EventType::KeyboardKeyEventType;
};