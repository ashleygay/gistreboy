#include <processor.hpp>

void Processor::execCurrentInstruction()
{
	//TODO: We get the next instruction to execute.
	// If any interrupts we deal with that first
	// Or we use programCounter and advance it to the next instruction

	//uint opcode = _memAccessor.getNextOpCode(programCounter.value, &args);
	//instructions[opcode].execute(&args);
	//return instructions[opcode].nbCycles();
}


void Processor::fetchNextInstruction()
{
	//TODO: do nothing
	//TODO: We get the next instruction to execute.
	// If any interrupts we deal with that first
	// Or we use programCounter and advance it to the next instruction

	//currentOpCode = _memAccessor.getNextOpCode(programCounter.value, &args);
	//instructions[opcode].execute(&args);
	//return instructions[opcode].nbCycles();
}

int Processor::getNbCycles() const
{
	//TODO: do stuff here
	return 42;
}
