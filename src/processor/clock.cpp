#include <clock.hpp>

void Clock::execStep()
{
	processor.fetchNextInstruction();
	int cycles = processor.getNbCycles();

	boost::asio::deadline_timer t(io, boost::posix_time::nanoseconds(period * cycles));

	processor.execCurrentInstruction();

	t.wait();
}
