#include <iostream>

#include "Application/ApplicationRunner.h"

#include "Application/States/MenuState.h"
#include "Application/States/GameState.h"

ApplicationRunner runner;

int main()
{
	if (!runner.initialize())
		return -1;
	runner.setState(new GameState(&runner));

	while (runner.is_running())
	{
		runner.update();
		runner.execute();
	}

	return 0;
}