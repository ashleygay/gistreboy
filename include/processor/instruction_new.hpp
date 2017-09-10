#pragma once

#include <functional>

template <typename... Args>
class MyInstruction
{
	public:
		MyInstruction(Args... args, std::function<void(Processor&, Args...)> func)
		{
			_args = std::make_tuple<Args...>(args...);
			_func = func;
		}

		int getOpCode(void) {return _opcode;}

		int getNbCycles(void) {return _nbcycles;}
	private:
		std::tuple<Args...> _args;
		std::function<void(Processor&, Args...)> _func;
		int _opcode;
		int _nbcycles;
};
