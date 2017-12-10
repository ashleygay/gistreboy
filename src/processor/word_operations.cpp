/*
 * File : word_operations.cpp
 *
 * File created by : Corentin Gay
 * File was created the : 06/12/2017
 */

#include <word_operations.hpp>

uint16_t make_word(uint8_t low, uint8_t high)
{
	DEBUG_STREAM << "MAKE_WORD: LOW: 0x" << std::hex
	<< (int)low << std::endl;

	DEBUG_STREAM << "MAKE_WORD: HIGH: 0x" << std::hex
	<< (int)high << std::endl;

	DEBUG_STREAM << "MAKE_WORD: RES: 0x" << std::hex
	<< (int)(low | (high << 8)) << std::endl;


	return (low | (high << 8));
}

uint8_t get_high(uint16_t word)
{
	DEBUG_STREAM << "GET_HIGH: 0x"
	<< std::hex << (int)(word >> 8)<< std::endl;

	return (word >> 8);
}

uint8_t get_low(uint16_t word)
{
	DEBUG_STREAM << "GET_LOW: 0x"
	<< std::hex << (int)(word & 0x00FF)<< std::endl;
	return (word & 0x00FF);
}

