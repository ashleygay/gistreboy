/*
 * File : file_content.hpp
 *
 * This class is used to pass around infos regarding a file content.
 * It is its data and its size (in bytes).
 *
 * File created by : Corentin Gay
 * File was created at : 23/10/2017
 */

#pragma once

#include <stdint.h>
#include <stdlib.h>

struct FileContent
{
	uint8_t * memory;
	size_t size;
};
