#include <clock.hpp>

void Clock::execStep()
{
	int cycles = _p->fetchNextStep();

	boost::asio::deadline_timer t(io, boost::posix_time::nanoseconds(period * cycles));

	_p->execCurrentInstruction();

	t.wait();
}
