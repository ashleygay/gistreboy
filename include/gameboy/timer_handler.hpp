#pragma once

#include <memory.hpp>
#include <debug.hpp>

class TimerHandler {

public:
	TimerHandler(Memory& mem);

	void step(int cpu_cycles);
private:
	void _interrupt();
	void _updateVariables();
	void _updateMemory();

	// Get clocks number associated with TAC
	int _getClockNumber();

private:
	Memory& _mem;

	int _elapsed_time = 0;

	int _clocks_nb = 0;

	bool _timer_enable = true;

	// FF04
	uint8_t _DIV = 0;
	int _div_counter = 0;

	// FF05
	uint8_t _TIMA = 0;

	// FF06
	uint8_t _TMA = 0;

/*
Bit	2 - Timer Enable	(0=Disable, 1=Enable)
Bits 1-0 - Main Frequency Divider
	00:	4096 Hz (Increase every 1024 clocks)
	01: 262144 Hz (	“	“	16 clocks)
	10: 65536 Hz (	“	“	64 clocks)
	11: 16386 Hz (	“	“	256 clocks)
*/
	std::bitset<3> _TAC;
	int _clocks_nbs[4] = {1024, 16, 64, 256};
};
