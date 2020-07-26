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
		std::cout << "Input: ";
		inputmanage.getinput();
		
		if (inputmanage[0].compare("define") == 0)
		{
			Method method;
			method.name = inputmanage[1];
			
			std::cout << "Define Syntax: ";
			inputmanage.getinput();
			method.syntax = inputmanage.return_parsed();
			
			std::cout << "Define the function: ";
			inputmanage.getinput();
			method.functiondef = inputmanage.return_parsed();

			for (std::size_t i = 0; i < method.syntax.size(); i++)
			{
				if ((method.input.size() == 0) && (method.name.compare(method.syntax[i]) != 0))
				{
					method.input.push_back(new var(method.syntax[i]));
				}
				else
				{
					for (std::size_t j = 0; j < method.input.size(); j++)
					{
						if (method.input[j]->varname.compare(method.syntax[i]) != 0)
						{
							method.input.push_back(new var(method.syntax[i]));
						}
					}
				}
			}
			method.setrelative();

			test.define(method);
			
		}
		else if (inputmanage[0].compare("run") == 0)
		{
			inputmanage.remove("run");
			std::cout << test.run(inputmanage.return_parsed()).back().value << std::endl;
			std::cout << std::endl;
		}
	}

	return 0;
}
