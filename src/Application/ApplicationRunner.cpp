#include "ApplicationRunner.h"

ApplicationRunner::ApplicationRunner()
	: Runner(), m_running(true) {
	// Empty
}

bool ApplicationRunner::initialize()
{	// For application initialization
	return 1;
}

bool ApplicationRunner::is_running()
{	 // Check if application is running
	return m_running;
}

void ApplicationRunner::terminate()
{	// For terminating the application
	m_running = false;
}

ApplicationState::ApplicationState(ApplicationRunner* _runner)
	: RunState(_runner) {
	application = _runner;
}