#include <iostream>
#include <string>
#include "stringprocess.hpp"
#include "mathstring.hpp"
#include "functiondeveloper.hpp"

int main()
{
	CommandString inputmanage;
	Subroutine test;
	
	for (;;)
	{
		inputmanage.getinput();
		if (inputmanage[0].compare("define") == 0)
		{
			test.define(inputmanage[1]);
			test.test();
		}
	}

	return 0;
}