#pragma once

enum class InternalEventType
{
	GameStart
};

class InternalEvent : public Event
{
public:
	InternalEvent(InternalEventType _type, void* _data)
		: event_type(_type), data(_data) {};

	void* get_data() { return data; }
	InternalEventType get_type() { return event_type; }

private:
	InternalEventType event_type;
	void* data;
};