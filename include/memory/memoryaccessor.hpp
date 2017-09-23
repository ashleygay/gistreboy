#pragma once

// This class is used to express the value of a range in memory. It is meant to
// be used to wrap all calls to read() and write() and deffers them when
// appropriate.


// T class should be able to handle the following calls:
//	uint16_t read(uint16_t address);
//	void write(uint16_t address, uint8_t value);

#include <stdint.h>

template <typename T>
class MemoryAccessor
{
	public:
		MemoryRange(uint16_t min, uint16_t max): _max(max),  _min(min)
		{
			_memory = T();
		}
	public:
		bool isInRange(uint16_t address)
			{return address >= _min && address <= _max;}

		uint16_t read(uint16_t address)
			{return _memory.read(address);}

		void write(uint8_t value, uint16_t address)
			{_memory.write(value, address);}

	private:
		uint16_t _max;
		uint16_t _min;
		T _memory;
};
