#pragma once

class FlagRegister {
	public:
		FlagRegister() { value = 0; }
		enum Flag { ZERO, SUBTRACT, HALFCARRY, CARRY };
		void setFlag(FlagRegister::Flag flag);
		void unsetFlag(FlagRegister::Flag flag);
		bool getFlag(FlagRegister::Flag flag);

	private:
		char value;
};
