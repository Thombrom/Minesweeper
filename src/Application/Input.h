#pragma once

#include "Event/Event.h"


/*
 * Static class for recording inputs
 * such that they can be queried without
 * nessecarily catching evnets
 */

class Input
{
public:
    static bool Key(KeyCode _code) { return key_state[static_cast<uint32_t>(_code)]; }
    static bool Key(MouseCode _code) { return key_state[static_cast<uint32_t>(_code)]; }

    static float MousePosX() { return cursor_pos_x; }
    static float MousePosY() { return cursor_pos_y; }

    static uint32_t WindowWidth() { return Input::window_width; }
    static uint32_t WindowHeight() { return Input::window_height; }

private:
    static bool key_state[350];

    static uint32_t window_width;
    static uint32_t window_height;

    static float cursor_pos_x;
    static float cursor_pos_y;

private:
    Input() = default;

public:
    static void RecordEvent(Event& _event)
    {
        EventDispatcher dispatcher(_event);
        dispatcher.execute<KeyPressedEvent>([](KeyPressedEvent& _event)->bool {
            size_t code = static_cast<size_t>(_event.get_key_code());
            Input::key_state[code] = true;
            return false;
        });

        dispatcher.execute<KeyReleasedEvent>([](KeyReleasedEvent& _event)->bool {
            size_t code = static_cast<size_t>(_event.get_key_code());
            Input::key_state[code] = false;
            return false;
        });

        dispatcher.execute<MouseButtonPressedEvent>([](MouseButtonPressedEvent& _event)->bool {
            size_t code = static_cast<size_t>(_event.get_mouse_code());
            Input::key_state[code] = true;
            return false;
        });

        dispatcher.execute<MouseButtonReleasedEvent>([](MouseButtonReleasedEvent& _event)->bool {
            size_t code = static_cast<size_t>(_event.get_mouse_code());
            Input::key_state[code] = false;
            return false;
        });

        dispatcher.execute<WindowResizeEvent>([](WindowResizeEvent& _event)->bool {
            Input::window_width = _event.get_width();
            Input::window_height = _event.get_height();
            return false;
        });

        dispatcher.execute<MouseMovedEvent>([](MouseMovedEvent& _event)->bool {
            Input::cursor_pos_x = _event.get_x();
            Input::cursor_pos_y = _event.get_y();
            return false;
        });
    }
};

