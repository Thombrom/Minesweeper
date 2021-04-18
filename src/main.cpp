#include <iostream>

#include "Runner/ApplicationRunner.h"

ApplicationRunner runner;

int main()
{
	if (!runner.initialize())
		return -1;

	while (runner.is_running())
	{
		runner.update();
		runner.execute();
	}

	return 0;
}