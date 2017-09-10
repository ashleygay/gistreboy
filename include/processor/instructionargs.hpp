#pragma once

#include <functional>
#include <registers.hpp>

struct Argument
{
	union value
	{
		uint8_t immediate_value = 0;
		std::reference_wrapper<Register> r;
		std::reference_wrapper<DRegister> dr;
	};
};


struct InstructionArgs
{
	Argument first_arg;
	Argument second_arg;
};
