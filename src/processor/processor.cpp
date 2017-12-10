/*
 * File : processor.cpp
 *
 * File created by : Arnaud Bastie
 * File was created at : 29/08/2017
 */

#include <processor.hpp>
#include <instruction.hpp>
#include <memory.hpp>
#include <iostream>

/* PUBLIC METHODS */

void Processor::enableIME()
{
	IME = true;
}

void Processor::disableIME()
{
	IME = false;
}


void Processor::enableIMEDelay()
{
	IMEDelay = true;
}

int Processor::step()
{
	if (!_mem)
	throw std::runtime_error("Memory or handler pointer not set.");

	int interrupts = _handleInterrupts();

	if (stopped || halted)
		return 0;

	if (!interrupts) {

		if (IMEDelay) {
			// Interrupts will be called on the next step
			IME = true;
			IMEDelay = false;
		}
		// No interrupts to handle and we are not halted/stopped
		_fetchNextInstruction();
		return _execCurrentInstruction();
	}
	else
		return interrupts;
}

int Processor::_handleInterrupts()
{
	//TODO maybe factorize IF and IE
	if (stopped) {
		DEBUG_STREAM << "STOPPED" << std::endl;
		// Check if any selected button is pressed
		uint8_t joypad_status = _mem->get_joypad();

		// Get bits [0-3] check that a button is pressed
		bool pressed = ~joypad_status & 0x0F;

		// Get bits [4-5], check that joypad is enabled
		bool selected = ~joypad_status & 0x30;

		if (pressed && selected) {
			// We end STOP mode.
			stopped = false;
			return 4;
		}
	}
	else { // We are either halted or doing an interrupt

		std::bitset<5> IF = _mem->get_interrupt_flags();
		std::bitset<5> IE = _mem->get_interrupt_enable();
		std::bitset<5> res = IF & IE;

		// Check that the selected interrupt is triggered
		int inter = res.any();
		if (inter && IME){
			// We compute the nth interrupt index
			unsigned int index = 0;
			while (!res[index] && (index < res.size())) {
				++index;
			}

			DEBUG_STREAM << "INTERRUPTING: " << index << std::endl;
			_mem->reset_interrupt_flag(index);
			halted = false;
			_setupInterrupt(index);
			return 5;
		}
	}
	// No interrupts, we return 0
	return 0;
}

void Processor::push_word(uint16_t word)
{
	DEBUG_STREAM << "	PUSHING 0x" <<  std::hex
	<< (int)word << std::dec << std::endl;
	_mem->write(get_low(word), --SP.value);
	_mem->write(get_high(word), --SP.value);
}

uint16_t Processor::pop_word()
{
	uint8_t high = _read(SP.value++);
	uint8_t low = _read(SP.value++);
	DEBUG_STREAM << "	POPING 0x" <<  std::hex
	<< (int)make_word(low, high) << std::dec<< std::endl;
	return make_word(low, high);
}

void Processor::_setupInterrupt(unsigned int interrupt)
{
	// We push PC onto the stack
	push_word(PC.value);
	// We set PC to the correct interrupt
	PC.value = INTERRUPT_VECTOR + (8 * interrupt);
	DEBUG_STREAM << "ISR: 0x" << std::hex << (int)PC.value
			<< std::dec << std::endl;
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
	DEBUG_STREAM << "PC: 0x"<< std::hex << (int)PC.value << std::dec;
	uint16_t opcode = _mem->read(PC.value);
	++PC.value;
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
	// Opcode is valid
	currentInstruction = iset.getInstruction(opcode);
	InstructionArg arg;

	//DEBUG_STREAM << "CODE: 0x"<< std::hex << (int)opcode << std::dec;
	DEBUG_STREAM << " : "<< currentInstruction->toStr();
	// This instruction takes an argument
	if(currentInstruction->hasArg()) {

		int size = currentInstruction->argSize();
		if (size == 1) { // We add a byte to the argument vector
			arg.byte = _mem->read(PC.value);
			DEBUG_STREAM << " 0x" << std::hex << (int)arg.byte << std::dec;
		}
		else { // Argument of size 2, we add a short to the argument vector
			uint16_t word = _mem->read(PC.value);
			++PC.value;
			word = word | (_mem->read(PC.value) << 8);
			arg.word = word;
			DEBUG_STREAM << " 0x" << std::hex << (int)arg.word << std::dec;
		}
		++PC.value;
	}
	DEBUG_STREAM << std::endl;
	currentInstruction->setArg(arg);
}

uint8_t Processor::_read(uint16_t address)
{
	return _mem->read(address);
}

void Processor::_write(uint8_t value, uint16_t address)
{
	_mem->write(value, address);
}

uint8_t Processor::_simple_read(uint16_t address)
{
	return _mem->simple_read(address);
}

void Processor::_simple_write(uint8_t value, uint16_t address)
{
	_mem->simple_write(value, address);
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
