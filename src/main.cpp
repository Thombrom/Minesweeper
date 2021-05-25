#include <iostream>

#include "Application/Application.h"
Application app;

int main()
{
	app.initialize();

	while (app.is_running())
		app.update();

	return 0;
}