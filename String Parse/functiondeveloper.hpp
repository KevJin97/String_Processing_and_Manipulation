#ifndef FUNCTIONDEVELOPER_HPP
#define FUNCTIONDEVELOPER_HPP

#include <cmath>
#include <string>
#include <vector>

struct Datatype
{
	std::vector<std::string> type;
};

struct var
{
	std::string varname;
	bool unknown;
};

std::vector<std::size_t*> parenthesis_pairing(std::vector<std::size_t> open, std::vector<std::size_t> closed)	//read order of parenthesis
{
	std::vector<std::size_t*> paired;
	std::size_t* openclose;
	bool* used = new bool[closed.size()];
	
	for (std::size_t index = 0; index < closed.size(); index++)	//initialize used
	{
		used[index] = false;
	}

	if (open.size() == closed.size())
	{
		std::size_t index = 0;
		while(index < open.size())
		{
			std::size_t sift = 0;
			openclose = new std::size_t[2];
			openclose[0] = open[open.size() - ++index];

			while (((used[sift] == true) || (open[open.size() - index] > closed[sift])) && (sift < closed.size()))
			{
				sift++;
			}

			openclose[1] = closed[sift];
			used[sift] = true;

			paired.push_back(openclose);
		}
	}
	else
	{
		//parenthesis aren't equal
	}
	delete[] used;
	return paired;
}

struct Method	//contains instruction set
{

};

//template<typename T>
class Subroutine
{
private:
	std::string functionname;
	std::vector<std::string> inputs;
	std::vector<std::string> basefunction_list;
	std::vector<std::string> queue;

public:
	Subroutine();
	~Subroutine();

	void queueing();
	//context
	//base functions
	//unsure, ask
	//queueing
};








//creating functions
/*

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

*/

#endif