#include <iostream>

#include "Application/ApplicationRunner.h"
ApplicationRunner runner;

int main()
{
	if (!runner.initialize())
		return -1;
	runner.set_state(new MenuState(&runner));

	while (runner.is_running())
	{
		runner.update();
		runner.execute();
	}

	return 0;
}