#include <iostream>
#include <string>

#include "stringprocess.hpp"
#include "MethodTypes.hpp"
#include "functiondeveloper.hpp"

int main()
{
	CommandString inputmanage;
	Subroutine test(new MathFunctions);

	for (;;)
	{
		inputmanage.getinput();
		std::vector<std::string> command = inputmanage.return_parsed();
		test.run(command);
	}

	return 0;
}
