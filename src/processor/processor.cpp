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
//	DEBUG_STREAM << "Processor STEP" << std::endl;
	if (!_handler || !_mem)
		throw std::runtime_error("Memory or handler pointer not set.");
	if (halted || stopped) {
		if (halted) {
			// Check that the selected interrupt is triggered
			std::bitset<8> IF = _mem->get_interrupt_flags();
			std::bitset<8> IE = _mem->get_interrupt_enable();
			std::bitset<8> res = IF & IE;

			int inter = res.any();
			if (inter) {

				//The handler will not do the interrupt
				// if IME is not set.

				(void)_handler->doInterrupt();
				halted = false;
				return 4;
			}
			else
				return 0;
		}
		else {
			// Check if any selected button is pressed
			uint8_t joypad_status = 0; _mem->read(0xFF00);

			// Get bits [0-3] check that a button is pressed
			int pressed = ~joypad_status & 0x0F;

			// Get bits [4-5], check that joypad is enabled
			int selected = ~joypad_status & 0x30;

			if (pressed && selected) {
				// We end STOP mode.
				stopped = false;
				return 4;
			}
		}
		return 0;
	}
	_fetchNextInstruction();
	return _execCurrentInstruction();
}


void Processor::HALT()
{
	halted = false;
}

void Processor::STOP()
{
	stopped = true;
}

/* PRIVATE METHODS */

int Processor::_execCurrentInstruction()
{
	currentInstruction->exec(this);
	return currentInstruction->nbCycles();
}

void Processor::_fetchNextInstruction()
{
	DEBUG_STREAM << "PC is 0x"<< std::hex << (int)PC.value << std::dec << std::endl;
	uint16_t opcode = _mem->read(PC.value);
	++PC.value;
//	DEBUG_STREAM << "Fetching 8 first bits 0x"<< std::hex << opcode << std::dec << std::endl;
	if (!iset.isValidOpCode(opcode)) {
		// We try the to get the instruction over 16bits
		opcode = (opcode << 8) | (_mem->read(PC.value));
		if (!iset.isValidOpCode(opcode)) {
			// We dont really care if the program crashes,
			// the rom is bad or there is a bug.
			_BUG("Unknown opcode : ", opcode);
			throw std::runtime_error("Unknown opcode, check the logs");
		}
		else //OpCode is on 16bits, we increment PC for args
			++PC.value;
	}
	DEBUG_STREAM << "OPCODE: 0x"<< std::hex << (int)opcode << std::dec << std::endl;
	// Opcode is valid
	currentInstruction = iset.getInstruction(opcode);
	InstructionArgs args;

	// We get each argument for the instruction, according to its length.
	for (int i = 0; i < currentInstruction->nbArgs() ; ++i) {

		int size = currentInstruction->argSize(i);
		if (size == 1) { // We add a byte to the argument vector
			uint8_t arg = _mem->read(PC.value);
//			DEBUG_STREAM << "Fetching argument 0x"<< std::hex
//				     << (int)arg << std::dec << std::endl;
			addByte(args, arg);
		}
		else { // Argument of size 1, we add a short to the argument vector
			uint16_t arg = _mem->read(PC.value);
			++PC.value;
			arg = arg | (_mem->read(PC.value) << 8);
//			DEBUG_STREAM << "Fetching argument 0x"<< std::hex
//				     << (int)arg << std::dec << std::endl;
			addShort(args, arg);
		}
		++PC.value;
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
	std::cout << "Register A : 0x"  << std::hex << (int)A.value << std::dec << std::endl;
	std::cout << "Register B : 0x"  << std::hex << (int)B.value << std::dec << std::endl;
	std::cout << "Register C : 0x"  << std::hex << (int)C.value << std::dec << std::endl;
	std::cout << "Register D : 0x"  << std::hex << (int)D.value << std::dec << std::endl;
	std::cout << "Register E : 0x"  << std::hex << (int)E.value << std::dec << std::endl;
	std::cout << "Register H : 0x"  << std::hex << (int)H.value << std::dec << std::endl;
	std::cout << "Register L : 0x"  << std::hex << (int)L.value << std::dec << std::endl;
	std::cout << "Program Counter : 0x"  << std::hex << PC.value << std::dec << std::endl;
	std::cout << "Stack Pointer : 0x"  << std::hex << SP.value << std::dec << std::endl;
}
