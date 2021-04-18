#pragma once

#include "../runner.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

/* ----------- CONFIGURATION STRUCT FOR STATE MEMORY ----------- */
struct ApplicationConfiguration
{

};

/* ----------- APPLICATION RUNNER IMPLEMENTATION --------------- */
class ApplicationRunner : public Runner
{	// Implementation of main application runner
public:
	ApplicationRunner();
	bool initialize();

	bool is_running();
	void terminate();

private:
	bool m_running;
};

/* ----------- APPLICATION STATE IMPLEMENTATION --------------- */
class ApplicationState : public RunState
{
public:
	ApplicationState(ApplicationRunner* _runner);

protected:
	ApplicationRunner* application;
};