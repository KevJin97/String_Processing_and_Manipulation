#include <iostream>
#include "stringprocess.hpp"
#include "mathstring.hpp"
#include "functiondeveloper.hpp"

int main()
{

	CommandString commandstring;
	//Subroutine function;

	for (;;)
	{
		std::cout << "Get Input: ";
		commandstring.getinput();

		std::cout << sizeof(int) << std::endl;

		commandstring.isolate("(");
		commandstring.isolate(")");
		commandstring.isolate(",");

		if (commandstring[0].compare("define") == 0)
		{
			std::vector<std::string> functionname;
			std::vector<std::string> inputs;

			std::vector<std::size_t> strtparent = commandstring.locate("(");
			std::vector<std::size_t> endparent = commandstring.locate(")");
			std::vector<std::size_t> comma = commandstring.locate(",");
			//progam safeties later

			functionname = commandstring.sublist(1, strtparent[0] -  1);

			if (strtparent[0] + 1 == endparent[0])	//no inputs
			{
				std::cout << std::endl;
				std::cout << "Function Name: " << commandstring.back2string(functionname) << std::endl;
				std::cout << "Input(s): NA" << std::endl;
				std::cout << "Num of Inputs: " << inputs.size() << std::endl;
			}
			else if (strtparent[0] + 1 < endparent[0])	//inputs, rewrite to automatically deal with commas in between parenthesis parameters, error if inputs.size() != comma.size() + 1
			{
				if (comma.size() != 0)
				{
					for (std::size_t i = 0, start = strtparent[0] + 1; start < endparent[0]; start++)
					{
						if (comma[i] == start)
						{
							start++;
						}
						inputs.push_back(commandstring[start]);
					}

					std::cout << std::endl;
					std::cout << "Function Name: " << commandstring.back2string(functionname) << std::endl;
					std::cout << "Input(s): " << commandstring.back2string(inputs) << std::endl;
					std::cout << "Num of Inputs: " << inputs.size() << std::endl;
				}
				else
				{
					for (std::size_t start = strtparent[0] + 1; start < endparent[0]; start++)
					{
						inputs.push_back(commandstring[start]);
					}

					std::cout << std::endl;
					std::cout << "Function Name: " << commandstring.back2string(functionname) << std::endl;
					std::cout << "Input(s): " << commandstring.back2string(inputs) << std::endl;
					std::cout << "Num of Inputs: " << inputs.size() << std::endl;
				}
			}
			else if (strtparent[0] + 1 > endparent[0])
			{
				//error in syntax
			}
			else
			{

			}
		}
		else
		{
			//JUST TESTING PARENTHESIS
			std::vector<std::size_t> open = commandstring.locate("(");
			std::vector<std::size_t> closed = commandstring.locate(")");
			std::vector<std::size_t*> paired = parenthesis_pairing(open, closed);
			
			std::cout << std::endl;

			for (std::size_t i = 0; i < commandstring.size(); i++)
			{
				std::cout << commandstring[i] << " ";
			}
			std::cout << std::endl;
			for (std::size_t i = 0; i < commandstring.size(); i++)
			{
				std::cout << i << " ";
			}
			std::cout << std::endl;
			std::cout << "Pairs:" << std::endl;
			for (std::size_t i = 0; i < paired.size(); i++)
			{
				std::cout << paired[i][0] << " , " << paired[i][1] << std::endl;
			}
		}
		std::cout << std::endl;
	}

	return 0;
}