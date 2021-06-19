#include <iostream>

#include "Application/Application.h"

int main()
{
    Application app;
	app.initialize();

	// Start menu 
	app.push_layer(new ApplicationLayer(&app));

	while (app.is_running())
		app.update();

	return 0;
}
