#pragma once
#include "Event.h"
#include "../Application/KeyCode.h"

class KeyEvent : public Event
{
public:
	KeyCode get_key_code() const { return m_keycode; }

	EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput);
protected:
	KeyEvent(const KeyCode _keycode)
		: m_keycode(_keycode) {};

	KeyCode m_keycode;
};

class KeyPressedEvent : public KeyEvent
{
public:
	KeyPressedEvent(const KeyCode _keycode, const uint32_t _repeat_amount)
		: KeyEvent(_keycode), m_repeat_amount(_repeat_amount) {};

	uint32_t get_repeat_amount() { return m_repeat_amount; }

	EVENT_CLASS_TYPE(EventType::KeyPressed);
private:
	uint32_t m_repeat_amount;
};

class KeyReleasedEvent : public  KeyEvent
{
public:
	KeyReleasedEvent(const KeyCode _keycode)
		: KeyEvent(_keycode) {};

	EVENT_CLASS_TYPE(EventType::KeyReleased);
};