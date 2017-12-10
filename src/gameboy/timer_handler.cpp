#include <timer_handler.hpp>

TimerHandler::TimerHandler(Memory& mem) : _mem(mem)
{
}

void TimerHandler::step(int cpu_step)
{
	_updateVariables();

	_div_counter += cpu_step;
	if (_div_counter >= 512)
		++_DIV;

	if (_timer_enable) {
		_elapsed_time += cpu_step;

		if (_elapsed_time >= _clocks_nb) {

			_elapsed_time -= _clocks_nb;
			if (_timer_enable) {
				if (_TIMA == 0xFF) { //we will have an overflow
					_interrupt();
					std::cout << "INTERRUPT TIMER"<< std::endl;
					_TIMA = _TMA;
				}
				++_TIMA;
			}
		}
	}

	_updateMemory();
}

void TimerHandler::_interrupt()
{
	_mem.set_interrupt_flag(Memory::Interrupt::TIMER);
}

void TimerHandler::_updateVariables()
{
	_DIV = _mem.simple_read(0xFF04);
	_TIMA = _mem.simple_read(0xFF05);
	_TMA = _mem.simple_read(0xFF06);
	_TAC = _mem.simple_read(0xFF07);
	_clocks_nb = _getClockNumber();
	_timer_enable = _TAC[2];
}

void TimerHandler::_updateMemory()
{
	_mem.simple_write(_DIV, 0xFF04);
	_mem.simple_write(_TIMA, 0xFF05);
	_mem.simple_write(_TMA, 0xFF06);
	uint8_t TAC = _TAC.to_ulong() & 0xFF;
	_mem.simple_write(TAC, 0xFF07);
}

int TimerHandler::_getClockNumber()
{
	// We return the value in the tab with index being bits 0-1
	return _clocks_nbs[_TAC.to_ulong() & 0x03];
}
