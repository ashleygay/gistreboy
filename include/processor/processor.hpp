#pragma once

#include "registers.hpp"

class Processor {
	public:
		static Processor& getInstance() {
			static Processor inst;
			return inst;
		}
		FlagRegister flagReg;

	private:
		Processor() {}

	public:
		Processor(Processor const&) = delete;
		void operator=(Processor const&)  = delete;
};
