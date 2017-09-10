#pragma once

#include <memory_accessor.hpp>

//TODO: think of a better solution

class CartridgeType
{
	public:
		virtual setup_cartridge(MemoryAccessor& m, Processor& p) = 0;
};


class Unused : CatridgeType
{
	public:
		virtual setup_cartridge(MemoryAccessor& m, Processor& p)
		{
			DEBUG_PRINT << "Cartridge type is unused,"
			<< "either something went wrong or the data is corrupted"
			<< std::endl;
		}
};
