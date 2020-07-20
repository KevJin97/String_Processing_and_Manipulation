#pragma once

#include <cmath>
#include <string>
#include <vector>
#include <map>
#include <utility>

#include "VariableClass.hpp"
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
	std::vector<std::string> queue;
	std::map<std::string, Method>* basemethods;

public:
	Subroutine();	//sets to default Method base
	Subroutine(Method* basemethod);	//new constructor for different types of Methods
	~Subroutine();	//delete memory from base

	void define(std::string functionname, std::vector<std::string> syntax, std::vector<std::string> functiondef);	//define function
	Method* return_method();
	var solve(std::vector<std::string> equation);
	bool checkfunction(Method function);	//check if defined function could be confused with a predefined function
	
	void operator=(Subroutine subroutine);
};

Subroutine::Subroutine()
{	
	this->function = new Method;
	this->queue = this->function->return_queue();
	this->basemethods = this->function->return_Method();
}

Subroutine::Subroutine(Method* basemethod)
{
	this->function = basemethod;
	this->queue = this->function->return_queue();
	this->basemethods = this->function->return_Method();
}

Subroutine::~Subroutine()
{
	delete function;
}

void Subroutine::define(std::string functionname, std::vector<std::string> syntax, std::vector<std::string> functiondef)
{
	this->function->define(functionname, syntax, functiondef);
}

Method* Subroutine::return_method()
{
	return this->function;
}

var Subroutine::solve(std::vector<std::string> equation)
{
	var ans;

	for (std::size_t i = 0; i < this->queue.size(); i++)
	{
		for (std::size_t j = 0; j < equation.size(); j++)
		{
			if (this->queue[i].compare(equation[j]) == 0)
			{

			}
		}
	}

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

void Subroutine::operator=(Subroutine subroutine)
{
	delete function;
	this->function = subroutine.return_method();
}