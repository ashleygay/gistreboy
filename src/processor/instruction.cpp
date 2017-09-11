#include <instruction.hpp>

decl_instruction(LD_BX, 0x06, 8)

void LD_BX::exec(InstructionArgs& args)
{
	Register& r = boost::get<RegRef>(args.first_arg);
	uint8_t val = boost::get<uint8_t>(args.second_arg);

	DEBUG_PRINT << "args.first_arg is " << r.value
	<< "\nargs.second_arg is " << val << std::endl; 
}
