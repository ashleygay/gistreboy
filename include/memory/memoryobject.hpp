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
		MemoryObject(std::vector<std::pair<uint16_t>> rang,
                             Processor& proc): range(rang),
					       processor(proc) { }

		bool isInRange(uint16_t address)
		{
			for (auto it = range.begin(); it != range.end();
			     it++)
			{
				if (range(address, it->first, it->second))
					return true;
			}
			return false;
		}

		bool range(uint16_t address, uint16_t min, uint16_t max)
		{
			return address >= min && address <= max;
		}

		virtual uint8_t read(uint16_t address) = 0;

		virtual void write(uint8_t value, uint16_t address) = 0;

		virtual void check_permissions_read(uint16_t address) = 0;

		virtual void check_permissions_write(uint16_t address,
						     uint8_t byte) = 0:
	protected:
		std::vector<std::pair<uint16_t, uint16_t>> range;
		Processor& processor;
};
