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

class MemoryObject
{
	public:
		MemoryObject(std::vector<std::pair<uint16_t, uint16_t>> 
			     range): _range(range) { }

		bool isInRange(uint16_t address)
		{
			for (auto it = _range.begin(); it != _range.end(); ++it)
			{
				if (addr_in_range(address, it->first, it->second))
					return true;
			}
			return false;
		}

		virtual uint8_t read(uint16_t address) = 0;

		virtual void write(uint16_t address, uint8_t byte) = 0;

		// FIXME: actually implement permissions
		virtual bool can_read(uint16_t address) = 0;
		virtual bool can_write(uint16_t address, uint8_t byte) = 0;

	protected:
	
		bool addr_in_range(uint16_t address, uint16_t min, uint16_t max)
		{
			return address >= min && address <= max;
		}

	protected:
		std::vector<std::pair<uint16_t, uint16_t>> _range;
};
