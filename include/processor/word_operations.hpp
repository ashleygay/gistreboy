/*
 * File : word_operations.hpp
 *
 * File created by : Corentin Gay
 * File was created at : 06/12/2017
 */

#pragma once

#include <stdint.h>
#include <debug.hpp>

uint16_t make_word(uint8_t low, uint8_t high);
uint8_t get_high(uint16_t word);
uint8_t get_low(uint16_t word);
