#pragma once

#include <functional>

#include <boost/variant.hpp>
#include <registers.hpp>

class Processor;

using DRegRef = std::reference_wrapper<DRegister>;
using RegRef = std::reference_wrapper<Register>;

using Argument = boost::variant<uint8_t, uint16_t, RegRef, DRegRef>;
using InstructionArgs = std::vector<Argument>;
