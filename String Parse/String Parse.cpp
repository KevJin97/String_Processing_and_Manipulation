#include <iostream>
#include "stringprocess.hpp"
#include "mathstring.hpp"
#include "functiondeveloper.hpp"

int main()
{
	CommandString commandstring;
	
	MathString test;
	for (;;)
	{
		test.getinput();
		test.test();
	}

	return 0;
}