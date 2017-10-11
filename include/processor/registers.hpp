#pragma once

struct Register {
	unsigned char value;
};

struct DRegister {
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

class InterruptRegister : private Register
{
	// This class represents InterruptEnable or InterruptFlag
	// It represents either that the interrupt is enabled
	// or that there is an interrupt pending

	// Bit 4 : Joypad
	// Bit 3 : Serial
	// Bit 2 : Timer
	// Bit 1 : LCD STAT
	// Bit 0 : VBLANK
	public:
		InterruptRegister() {value = 0x00;}
		enum Interrupt { VBLANK, LCD_STATUS, TIMER, SERIAL, JOYPAD };
		void setInterrupt(InterruptRegister::Interrupt interrupt);
		void resetInterrupt(InterruptRegister::Interrupt interrupt);
};
