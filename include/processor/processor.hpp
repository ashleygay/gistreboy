#pragma once

#include "registers.hpp"

class Processor {
	public:
		static Processor& getInstance() {
			static Processor inst;
			return inst;
		}
		FlagRegister flagReg;
		Register registerB;
		Register registerC;
		Register registerD;
		Register registerE;
		Register registerH;
		Register registerL;

	private:
		DRegister programCounter;
		DRegister stackPointer;


	private:
		Processor()
		{
			programCounter.value = 0x100;
			stackPointer.value = 0xfffe;
		}

	public:
		Processor(Processor const&) = delete;
		void operator=(Processor const&)  = delete;
};
