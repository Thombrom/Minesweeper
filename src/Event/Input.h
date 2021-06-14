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
    static bool Key(KeyCode _code)   { return key_state[static_cast<uint32_t>(_code)]; }
    static bool Key(MouseCode _code) { return key_state[static_cast<uint32_t>(_code)]; }

    static bool WindowWidth()        { return window_width; }
    static bool WindowHeight()       { return window_height; }

private:
    static bool key_state[350];

    static uint32_t window_width;
    static uint32_t window_height;

private:
    Input() = default;

public:
    static void RecordEvent(Event& _event)
    {
        EventDispatcher dispatcher(_event);
        dispatcher.on<KeyPressedEvent>([](KeyPressedEvent& _event)->bool {
            Input::key_state[_event.get_key_code()] = true;
            return false;
        });

        dispatcher.on<KeyReleasedEvent>([](KeyReleasedEvent& _event)->bool {
            Input::key_state[_event.get_key_code()] = false;
            return false;
        });

        dispatcher.on<MouseKeyPressedEvent>([](MouseKeyPressedEvent& _event)->bool {
            Input::key_state[_event.get_key_code()] = true;
            return false;
        })

        dispatcher.on<MouseKeyReleasedEvent>([](MouseKeyReleasedEvent& _event)->bool {
            Input::key_state[_event.get_key_code()] = false;
            return false;
        });

        dispatcher.on<WindowResizeEvent>([](WindowResizeEvent& _event)->bool {
            Input::window_width  = _event.get_width();
            Input::window_height = _event.get_height();
            return false;
        });
    }
}

