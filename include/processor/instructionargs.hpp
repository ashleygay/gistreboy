#pragma once

#include <functional>
#include <vector>

#include <boost/variant.hpp>
#include <registers.hpp>

class Processor;

using Argument = boost::variant<uint8_t, uint16_t>;
using InstructionArg = std::vector<Argument>;

// Helper functions to add correponding elements to a vector
void addShort(InstructionArg& arg, uint16_t val);
void addByte(InstructionArg& arg, uint8_t val);
