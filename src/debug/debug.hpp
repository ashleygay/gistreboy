#pragma once

#include <iostream>

namespace std
{
	struct nullstream : ostream
	{
		nullstream(): std::ios(0), std::ostream(0) {}
	};
}

#ifdef DEBUG_PRINT_ACTIVATED 
	#define DEBUG_PRINT std::cout 
#else
	#define DEBUG_PRINT std::nullstream() 
#endif 
