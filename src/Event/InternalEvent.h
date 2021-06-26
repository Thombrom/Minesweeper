#pragma once

enum class InternalEventType
{
	CHANGE_START_MENU,
	CHANGE_START_GAME,
	CHANGE_START_SETTINGS,
	CHANGE_EXIT_GAME,

    GAME_END,
	EXIT_APP
};

class InternalEvent : public Event
{
public:
	InternalEvent(InternalEventType _type, void* _data)
		: event_type(_type), data(_data) {};

	void* get_data() { return data; }
	InternalEventType get_type() { return event_type; }

	EVENT_CLASS_CATEGORY(EventCategoryInternal);
	EVENT_CLASS_TYPE(EventType::Internal);

private:
	InternalEventType event_type;
	void* data;
};
