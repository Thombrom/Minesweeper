#pragma once

#include "Event/Event.h"

class WindowResizeEvent : public Event
{
public:
	WindowResizeEvent(uint32_t _width, uint32_t _height)
		: height(_height), width(_width) {};

	uint32_t get_width() { return width; }
	uint32_t get_height() { return height; }

	EVENT_CLASS_TYPE(EventType::WindowResize)
	EVENT_CLASS_CATEGORY(EventCategoryApplication | EventCategoryInput)

private:
	uint32_t width, height;
};

class WindowCloseEvent : public Event
{
public:
	WindowCloseEvent() = default;

	EVENT_CLASS_TYPE(EventType::WindowClose)
	EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

class WindowFocusEvent : public Event
{
public:
	WindowFocusEvent() = default;

	EVENT_CLASS_TYPE(EventType::WindowFocus)
	EVENT_CLASS_CATEGORY(EventCategoryApplication | EventCategoryInput)
};

class WindowLostFocusEvent : public Event
{
public:
	WindowLostFocusEvent() = default;

	EVENT_CLASS_TYPE(EventType::WindowLostFocus)
	EVENT_CLASS_CATEGORY(EventCategoryApplication | EventCategoryInput)
};

class WindowMovedEvent : public Event
{
public:
	WindowMovedEvent(int _x, int _y)
		: x(_x), y(_y) {};

	int get_x_pos() { return x; }
	int get_y_pos() { return y; }

	EVENT_CLASS_TYPE(EventType::WindowMoved)
	EVENT_CLASS_CATEGORY(EventCategoryApplication | EventCategoryInput)

private:
	int x, y;
};