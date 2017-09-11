#pragma once

#include <functional>

#include <boost/variant.hpp>
#include <registers.hpp>

class Processor;

using DRegRef = std::reference_wrapper<DRegister>;
using RegRef = std::reference_wrapper<Register>;

struct InstructionArgs
{
	using Argument = boost::variant<uint8_t, uint16_t,
					RegRef, DRegRef>;
	Argument first_arg;
	Argument second_arg;
};
