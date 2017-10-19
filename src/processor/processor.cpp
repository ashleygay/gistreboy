/*
 * File : processor.cpp
 *
 * File created by : Arnaud Bastie
 * File was created at : 29/08/2017
 */

#include <processor.hpp>
#include <instruction.hpp>

void Processor::execCurrentInstruction()
{
	currentInstruction->exec(this);
}


int Processor::_fetchNextInstruction()
{
	uint16_t opcode = 0; /*_mem.read(programCounter.value);*/
	if (!iset.isValidOpCode(opcode)) {
		// We try the to get the instruction over 16bits
//		opcode = (opcode << 8) | _mem.read(++programCounter.value);
		if (!iset.isValidOpCode(opcode)) {
			return _BUG("Unknown opcode : ", opcode);
		}
	}
	// Opcode is valid
	currentInstruction = iset.getInstruction(opcode);
	InstructionArgs args;

	// We get each argument for the instruction, according to its length.
	for (int i = 0; i < currentInstruction->nbArgs() ; ++i) {

		uint16_t arg = 0;
		for (int size = 0; size < currentInstruction->argSize(i); ++size) {

//			arg = (arg << 8) | _mem.read(++programCounter.value);
		}
		addShort(args, arg);
	}
	currentInstruction->setArgs(args);
	return currentInstruction->nbCycles();
}

int Processor::fetchNextStep()
{
	return _fetchNextInstruction();
}

int Processor::_BUG(std::string str, int value)
{
	std::cout << str << "0x" << std::hex << value << std::dec << std::endl;
	return -1;
}
