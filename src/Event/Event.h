#pragma once
#include <iostream>

/*
	Enum for the different event types and
	event categories. Adopted from Hazel Engine
*/
enum class EventType
{
	None = 0,
	WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
	KeyPressed, KeyReleased, KeyTyped,
	MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled,
	Internal
};

enum EventCategory
{
	None = 0,
	EventCategoryApplication =	1 << 0,
	EventCategoryInput =		1 << 1,
	EventCategoryKeyboard =		1 << 2,
	EventCategoryMouse =		1 << 3,
	EventCategoryMouseButton =	1 << 4,
	EventCategoryInternal =		1 << 5,
};

/*
	Class for events

	Events should derive from this class
	and all nessecary information about
	that event should be in the derived
	class
*/

#define BIND_EVENT_FN(function) std::bind(&function, this, std::placeholders::_1)
#define EVENT_CLASS_CATEGORY(eventclass) virtual int get_category_flags() const override { return eventclass; }
#define EVENT_CLASS_TYPE(eventtype) static EventType StaticType() { return eventtype; };\
										virtual const char* get_name() const override { return #eventtype; }; \
										virtual EventType get_event_type() const override { return eventtype; };

class Event
{
public:
	virtual EventType get_event_type() const = 0;
	virtual const char* get_name() const = 0;
	virtual int get_category_flags() const = 0;
	
	bool is_in_category(EventCategory _category) { return get_category_flags() & _category; }

public:
	bool is_handled = false;
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

	template<typename EventType, typename EventFunc>
	bool execute(EventFunc _function) {
		if (m_event->get_event_type() == EventType::StaticType() && !m_event->is_handled)
		{
			m_event->is_handled = _function(static_cast<EventType&>(*m_event));
			return true;
		}
		return false;
	}

protected:
	Event* m_event;
};

#include "KeyEvent.h"
#include "MouseEvent.h"
#include "ApplicationEvent.h"
#include "InternalEvent.h"