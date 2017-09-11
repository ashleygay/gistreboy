#include <instruction.hpp>


void LD_BX::exec(InstructionArgs& args)
{
	//Register& r = boost::get<RegRef>(args.first_arg);
	//uint8_t val = boost::get<uint8_t>(args.second_arg);

	Processor& proc = Processor::getInstance();
	proc.regissterB = val;

	DEBUG_PRINT << "args.first_arg is " << r.value
	<< "\nargs.second_arg is " << val << std::endl; 
}
