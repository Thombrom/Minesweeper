#include "runner.h"

RunState::RunState(Runner* _runner)
	: runner(_runner) {
	// Otherwise empty
}

void RunState::set_state(RunState* _state)
{
	delete runner->m_state;
	runner->m_state = _state;
}



Runner::Runner() 
{
	// Empty
}

Runner::Runner(RunState* _state)
	: m_state(_state) {
	// Empty
}

Runner::~Runner()
{	// Make sure to clear state
	delete m_state;
}

void Runner::setState(RunState* _state)
{
	m_state = _state;
}

void Runner::execute()
{
	if (!m_state)
		return;
	m_state->execute();
}

void Runner::update()
{
	if (!m_state)
		return;
	m_state->update_state();
}
