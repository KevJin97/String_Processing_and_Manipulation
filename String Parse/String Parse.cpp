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
		test.run(inputmanage.return_parsed);
	}

	return 0;
}
