#pragma once

#include "Event/Event.h"
#include "Application/KeyCode.h"

class MouseButtonEvent : public Event
{
public:
	MouseCode get_mouse_code() { return key; }

	EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput);

protected:
	MouseButtonEvent(MouseCode _keycode)
		: key(_keycode) {};
		
private:
	MouseCode key;
};

class MouseButtonPressedEvent : public MouseButtonEvent
{
public:
	MouseButtonPressedEvent(MouseCode _keycode)
		: MouseButtonEvent(_keycode) {};

	EVENT_CLASS_TYPE(EventType::MouseButtonPressed)
};

class MouseButtonReleasedEvent : public MouseButtonEvent
{
public:
	MouseButtonReleasedEvent(MouseCode _keycode)
		: MouseButtonEvent(_keycode) {};

	EVENT_CLASS_TYPE(EventType::MouseButtonReleased)
};

class MouseMovedEvent : public Event
{
public:
	MouseMovedEvent(const float _x, const float _y)
		: m_x(_x), m_y(_y) {};

	float get_x() const { return m_x; }
	float get_y() const { return m_y; }

	EVENT_CLASS_TYPE(EventType::MouseMoved)
	EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput);

private:
	float m_x, m_y;
};

class MouseScrollEvent : public Event
{
public:
	MouseScrollEvent(const float _x, const float _y)
		: s_x(_x), s_y(_y) {};

	float get_x_offset() const { return s_x; }
	float get_y_offset() const { return s_y; }

	EVENT_CLASS_TYPE(EventType::MouseScrolled)
	EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput);

private:
	float s_x, s_y;
};