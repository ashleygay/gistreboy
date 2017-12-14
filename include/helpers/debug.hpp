/*
 * File : debug.hpp
 *
 * This file allows print out debug information that will not be compiled if
 * DEBUG_STREAM_ACTIVATED is not set
 * Allows to do something like this DEBUG_STREAM << "TEST" << std::endl;
 *
 * File created by : Corentin Gay
 * File was created the : 08/09/2017
 */

#pragma once

#include <iostream>

namespace std
{
	struct nullstream : ostream
	{
		nullstream(): std::ios(0), std::ostream(0) {}
	};
}

#ifdef DEBUG_STREAM_ACTIVATED
	#define DEBUG_STREAM std::cout
#else
	#define DEBUG_STREAM std::nullstream()
#endif

#ifdef BENCH_STREAM_ACTIVATED
	#define BENCH_STREAM std::cout
#else
	#define BENCH_STREAM std::nullstream()
#endif
