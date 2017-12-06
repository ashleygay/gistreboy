/*
 * File : word_operations.cpp
 *
 * File created by : Corentin Gay
 * File was created the : 06/12/2017
 */

#include <word_operations.hpp>

uint16_t make_word(uint8_t low, uint8_t high)
{
	return (low | (high << 8));
}

uint8_t get_high(uint16_t word)
{
	return (word >> 8);
}

uint8_t get_low(uint16_t word)
{
	return (word & 0xFF);
}

