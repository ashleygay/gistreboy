#include <clock.hpp>

void Clock::connectProc(Processor *p)
{
	processor = p;
}

void Clock::execStep()
{
	// We assume that our code executes instantly.
	//TODO: We could actually time the code execution.

	processor->fetchNextInstruction();
	int cycles = processor->getNbCycles();

	boost::asio::deadline_timer t(io, boost::posix_time::nanoseconds(period * cycles));

	processor->execCurrentInstruction();

	t.wait();
}
