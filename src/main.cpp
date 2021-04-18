#include <iostream>

#include "Application/ApplicationRunner.h"
#include "Application/States/MenuState.h"

ApplicationRunner runner;

int main()
{
	if (!runner.initialize())
		return -1;
	runner.setState(new MenuState(&runner));

	while (runner.is_running())
	{
		runner.update();
		runner.execute();
	}

	return 0;
}