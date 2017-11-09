/*
 * File : processor.cpp
 *
 * File created by : Arnaud Bastie
 * File was created at : 29/08/2017
 */

#include <processor.hpp>
#include <instruction.hpp>
#include <interrupthandler.hpp>
#include <memory.hpp>

/* PUBLIC METHODS */

void Processor::enableIME()
{
	_handler->enableIME();
}

void Processor::disableIME()
{
	_handler->disableIME();
}


void Processor::enableIMEDelay()
{
	_handler->enableIMEDelay();
}

int Processor::step()
{
	_fetchNextInstruction();
	return _execCurrentInstruction();
}

/* PRIVATE METHODS */

int Processor::_execCurrentInstruction()
{
	currentInstruction->exec(this);
	return currentInstruction->nbCycles();
}

void Processor::_fetchNextInstruction()
{
	uint16_t opcode = _mem->read(PC.value);
	if (!iset.isValidOpCode(opcode)) {
		// We try the to get the instruction over 16bits
		opcode = (opcode << 8) | _mem->read(++PC.value);
		if (!iset.isValidOpCode(opcode)) {
			// We dont really care if the program crashes,
			// the rom is bad or there is a bug.
			_BUG("Unknown opcode : ", opcode);
			throw std::runtime_error("Unknown opcode, check the logs");
		}
	}
	// Opcode is valid
	currentInstruction = iset.getInstruction(opcode);
	InstructionArgs args;

	// We get each argument for the instruction, according to its length.
	for (int i = 0; i < currentInstruction->nbArgs() ; ++i) {

		uint16_t arg = 0;

		int size = 0;
		for (; size < currentInstruction->argSize(i); ++size)
			arg = (arg << 8) | _mem->read(++PC.value);

		addShort(args, arg);
	}
	currentInstruction->setArgs(args);
}

uint8_t Processor::_read(uint16_t address)
{
	return _mem->read(address);
}

void Processor::_write(uint8_t value, uint16_t address)
{
	_mem->write(value, address);
}

void Processor::_BUG(std::string str, int value) const
{
	//We dump everything.
	std::cout << str << "0x" << std::hex << value << std::dec << std::endl;
	std::cout << "REGISTERS" << std::endl;
	std::cout << "Register A : 0x"  << std::hex << A.value << std::endl;
	std::cout << "Register B : 0x"  << std::hex << B.value << std::endl;
	std::cout << "Register C : 0x"  << std::hex << C.value << std::endl;
	std::cout << "Register D : 0x"  << std::hex << D.value << std::endl;
	std::cout << "Register E : 0x"  << std::hex << E.value << std::endl;
	std::cout << "Register H : 0x"  << std::hex << H.value << std::endl;
	std::cout << "Register L : 0x"  << std::hex << L.value << std::endl;
	std::cout << "Program Counter : 0x"  << std::hex << PC.value << std::endl;
	std::cout << "Stack Pointer : 0x"  << std::hex << SP.value << std::endl;
}
