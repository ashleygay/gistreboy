#pragma once

#include <processor.hpp>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

	//TODO: clock will call CPU to process next instruction
	// then it will wait to adjust to the number of cycles

	//TODO: get actual CPU frequence and compute the correct frequence

// All cycles are in actual clock cycles

class Clock
{
	public:
		Clock(Processor* p): _p(p)
		{
			boost::asio::io_service io;
			boost::asio::deadline_timer t(io);
		}

		// Execute a step of the connected CPU.
		void execStep();

		// Connect a CPU to the clock.
		void connectProc();

	private:
		boost::asio::io_service io;
		Processor *_p;

		// Desired frequence for the emulator
		// const unsigned int freq = 4194304; // In Hz
		//TODO: compute it based on the frequency.
		const unsigned int period = 238; // In nanoseconds
};
