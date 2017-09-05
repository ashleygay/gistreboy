#pragma once

class Register {
	public:
		unsigned char value;
};

class DRegister {
	public:
		unsigned short value;
};

class FlagRegister : private Register {
	public:
		FlagRegister() { value = 0; }
		enum Flag { ZERO, SUBTRACT, HALFCARRY, CARRY };
		void setFlag(FlagRegister::Flag flag);
		void unsetFlag(FlagRegister::Flag flag);
		bool getFlag(FlagRegister::Flag flag);
};
