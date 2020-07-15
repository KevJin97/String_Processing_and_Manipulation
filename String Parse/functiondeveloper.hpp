#ifndef FUNCTIONDEVELOPER_HPP
#define FUNCTIONDEVELOPER_HPP

#include <cmath>
#include <string>
#include <vector>
#include <map>
#include <utility>

#include "stringprocess.hpp"
#include "MethodTypes.hpp"

std::vector<std::size_t*> parenthesis_pairing(std::vector<std::size_t> open, std::vector<std::size_t> closed)	//read order of parenthesis, make sure to erase data later. New algorithm ready
{
	std::vector<std::size_t*> paired;
	std::size_t* openclose;
	bool* used = new bool[closed.size()];

	for (std::size_t index = 0; index < closed.size(); index++)	//initialize used
	{
		used[index] = false;
	}

	if (open.size() == closed.size() && open.size() != 0)
	{
		std::size_t index = 0;
		while (index < open.size())
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
		delete[] used;
	}
	else
	{
		//parenthesis aren't equal
	}
	return paired;
}

//TODO: create a natural language subroutine that inherits from this one
//Subroutine takes instruction sets in Method and processes it
class Subroutine
{
protected:
	Method* function;

public:
	Subroutine();	//sets to default Method base
	Subroutine(Method* basemethod);	//new constructor for different types of Methods
	~Subroutine();	//delete memory from base

	Method* return_method();
	std::size_t basefunction(std::string functionname, std::vector<var> inputs);	//returns the index the base function is located at
	var solve();
	var solve(CommandString command);
	bool checkfunction(Method function);	//check if defined function could be confused with a predefined function
	
	void operator=(Subroutine subroutine);

	//testcode
	void test()
	{
		
	}
};

Subroutine::Subroutine()
{	//temporary until MathString is finished
	this->function = new MathMethod;
	//base = new Method;	//replace with this
}

Subroutine::Subroutine(Method* basemethod)
{
	this->function = basemethod;
}

Subroutine::~Subroutine()
{
	delete function;
}

Method* Subroutine::return_method()
{
	return this->function;
}

std::size_t Subroutine::basefunction(std::string functionname, std::vector<var> inputs)
{
	/*
	std::size_t index;

	for (index = 0; index < this->basefunction_list.size(); index++)
	{
		if ((functionname.compare(this->basefunction_list[index].name)) == 0 && (inputs.size() == this->basefunction_list[index].input.size()))
		{
			return index;
		}
	}

	return this->basefunction_list.size();	//return the size value (index is outside of the range)
	*/
	return 0;
}

var Subroutine::solve()
{
	var ans;

	return ans;
}

var Subroutine::solve(CommandString command)
{
	var ans;

	return ans;
}

bool Subroutine::checkfunction(Method function)
{
	/*
	if (this->basefunction(function.name, function.input) == this->basefunction_list.size())	//false if function doesn't exist
	{
		return false;
	}
	else
	{
		return true;
	}
	*/
	return true;
}

void parenthesis(CommandString& parsed, std::size_t open, std::size_t close)
{
	
}

void Subroutine::operator=(Subroutine subroutine)
{
	delete function;
	this->function = subroutine.return_method();
}

#endif