#include "instruction.hpp"
#include "processor.hpp"

#define decl_LD_RegCst_exec(reg)\
	void LD_##reg##X::execute() \
	{\
		Processor& proc = Processor::getInstance();\
		proc.register##reg.value = this->value;\
	}
