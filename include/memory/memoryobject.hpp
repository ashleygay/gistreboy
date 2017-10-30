#pragma once

// This class is used to express the value of a range in memory. It is meant to
// be used to wrap all calls to read() and write() and deffers them when
// appropriate.


// T class should be able to handle the following calls:
//	uint16_t read(uint16_t address);
//	void write(uint16_t address, uint8_t value);

#include <stdint.h>
#include <vector>
#include <utility>
#include <processor.hpp>

class MemoryObject
{
	public:

		MemoryObject() {}

		MemoryObject(Processor* proc,
			     std::vector<std::pair<uint16_t, uint16_t>> 
			     rang): processor(proc), range(rang) { }

		bool isInRange(uint16_t address)
		{
			for (auto it = range.begin(); it != range.end();
			     it++)
			{
				if (addr_range(address, it->first,
					       it->second))
					return true;
			}
			return false;
		}

		bool addr_range(uint16_t address, uint16_t min,
				uint16_t max)
		{
			return address >= min && address <= max;
		}

		virtual uint8_t read(uint16_t address) = 0;

		virtual void write(uint16_t address, uint8_t byte) = 0;

		// FIXME: actually implement permissions
		virtual bool can_read(uint16_t address) = 0;
		virtual bool can_write(uint16_t address, uint8_t byte) = 0;

	protected:
		Processor* processor;
		std::vector<std::pair<uint16_t, uint16_t>> range;
};
