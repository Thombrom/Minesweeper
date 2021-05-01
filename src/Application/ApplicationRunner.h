#pragma once
#include <iostream>
#include <functional>
#include <time.h>

#include "../runner.h"
#include "Window/window.h"
#include "Event/Event.h"

/* ----------- CONFIGURATION STRUCT FOR STATE MEMORY ----------- */
struct ApplicationConfiguration
{
	Window* window;
};

/* ----------- APPLICATION RUNNER IMPLEMENTATION --------------- */
class ApplicationState;

class ApplicationRunner : public Runner
{	// Implementation of main application runner
public:
	ApplicationRunner();
	~ApplicationRunner();
	bool initialize();

	void on_event(Event& _event);

	bool is_running();
	void terminate();
	void internal_execute();
	ApplicationState* get_state();

	ApplicationConfiguration configuration;

private:
	void set_event_hooks();

	bool m_running;
};

/* ----------- APPLICATION STATE IMPLEMENTATION --------------- */
class ApplicationState : public RunState
{
public:
	ApplicationState(ApplicationRunner* _runner);

	virtual void on_event(Event& _event) = 0;

	void clear_screen();
	void set_cursor(uint32_t _x, uint32_t _y);

protected:
	ApplicationRunner* application;
};

#include "States/GameState.h"
#include "States/MenuState.h"