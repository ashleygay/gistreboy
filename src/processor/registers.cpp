#include <iostream>

#include "registers.hpp"

void FlagRegister::setFlag(FlagRegister::Flag flag)
{
	switch(flag) {
		case ZERO:
			value |= 0x80;
			break;
		case SUBTRACT:
			value |= 0x40;
			break;
		case HALFCARRY:
			value |= 0x20;
			break;
		case CARRY:
			value |= 0x10;
			break;
	}
}

void FlagRegister::unsetFlag(FlagRegister::Flag flag)
{
	switch(flag) {
		case ZERO:
			value &= 0x70;
			break;
		case SUBTRACT:
			value &= 0xb0;
			break;
		case HALFCARRY:
			value &= 0xd0;
			break;
		case CARRY:
			value &= 0xe0;
			break;
	}
}

bool FlagRegister::getFlag(FlagRegister::Flag flag)
{
	switch(flag) {
		case ZERO:
			return value & 0x80;
		case SUBTRACT:
			return value & 0x40;
		case HALFCARRY:
			return value & 0x20;
		case CARRY:
			return value & 0x10;
	}
	return false;
}
