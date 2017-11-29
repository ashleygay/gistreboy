#pragma once

#include <functional>
#include <vector>

#include <boost/variant.hpp>
#include <registers.hpp>

class Processor;

using DRegRef = std::reference_wrapper<DRegister>;
using RegRef = std::reference_wrapper<Register>;

using Argument = boost::variant<uint8_t, uint16_t, RegRef, DRegRef>;
using InstructionArgs = std::vector<Argument>;

// Helper functions to add correponding elements to a vector
void addShort(InstructionArgs& args, uint16_t val);
void addByte(InstructionArgs& args, uint8_t val);
void addRegRef(InstructionArgs& args, RegRef reg);
void addDRegRef(InstructionArgs& args, DRegRef ref);
