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
		std::vector<std::string> command = inputmanage.return_parsed();
		
		if (command[0].compare("define") == 0)
		{
			Method method;
			method.name = command[1];

			std::cout << "Enter syntax: ";
			inputmanage.getinput();
			method.syntax = inputmanage.return_parsed();

			std::cout << "Define function: ";
			inputmanage.getinput();
			method.functiondef = inputmanage.return_parsed();

			for (std::size_t i = 0; i < method.syntax.size(); i++)
			{
				if (method.name.compare(method.syntax[i]) != 0)
				{
					if (method.input.size() == 0)
					{
						method.input.push_back(method.syntax[i]);
					}
					else
					{
						for (std::size_t j = 0; j < method.input.size(); j++)
						{
							if (method.input[j].varname.compare(method.syntax[i]) != 0)
							{
								method.input.push_back(method.syntax[i]);
							}
						}
					}
				}
			}
			method.setrelative();

			test.define(method);
		}
		else if (command[0].compare("run") == 0)
		{
			std::cout << test.run(command).back().value << std::endl;
		}
	}

	return 0;
}
