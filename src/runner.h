#pragma once

class Runner;

class RunState
{
public:
	virtual void update_state() = 0;
	virtual void execute() = 0;

protected:
	RunState(Runner* _runner);
	void set_state(RunState* _state);

	Runner* runner;
};

class Runner
{
	friend class RunState;
public:
	Runner();
	Runner(RunState* _state);
	~Runner();

	void setState(RunState* _state);
	void update();
	void execute();

private:
	RunState* m_state;
};