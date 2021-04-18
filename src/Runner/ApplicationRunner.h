#pragma once

#include "../runner.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

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

class ApplicationState
{

};