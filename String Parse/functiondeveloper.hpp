#pragma once

#include <cmath>
#include <string>
#include <vector>
#include <map>
#include <utility>

#include "Var.hpp"
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

struct Queue
{
	std::string functionname;
	std::vector<std::size_t> functionlocations;

	Queue() {}
	Queue(std::string name);

	void operator=(std::string name);
};

Queue::Queue(std::string name)
{
	this->functionname = name;
}

void Queue::operator=(std::string name)
{
	functionname = name;
}


//TODO: create a natural language subroutine that inherits from this one
//Subroutine takes instruction sets in Method and processes it
class Subroutine
{
protected:
	Functions* base;	//holds all base functions
	std::vector<Queue> queue;	//order default operators will be run
	std::map <std::string, Method> method_list;	//list of user-defined functions
	std::map <std::string, var> variable_list;	//list of variables that get defined

public:
	Subroutine();
	Subroutine(Functions* type);
	~Subroutine();

	void define(Method& method);
	std::vector<var> run(std::vector<std::string>& command);	//runs the inputted command and returns list of outputs
	var run_method(Method& method, std::size_t& operatorlocation, std::vector<std::string>& command);	//run user-defined methods
};

Subroutine::Subroutine()
{
	this->base = new Functions;
	
	for (std::size_t i = 0; i < base->queue.size(); i++)
	{
		this->queue.push_back(base->queue[i]);
	}
}

Subroutine::Subroutine(Functions* type)
{
	this->base = type;
	
	for (std::size_t i = 0; i < base->queue.size(); i++)
	{
		this->queue.push_back(base->queue[i]);
	}
}

Subroutine::~Subroutine()
{
	delete this->base;
}

void Subroutine::define(Method& method)
{
	this->method_list.insert(std::pair<std::string, Method>(method.name, method));
	this->queue.insert(this->queue.begin(), method.name);
}

std::vector<var> Subroutine::run(std::vector<std::string>& command)
{
	std::size_t* keeptrack = new std::size_t[command.size()];	//keep track of which sections has been used in command
	for (std::size_t i = 0; i < command.size(); i++)	//initialize keeptrack to size of command
	{
		keeptrack[i] = command.size();
	}

	std::size_t numberofoperators = 0;	//number of operators which determines number of outputs

	for (std::size_t i = 0; i < command.size(); i++)	//retrieves total number of operators
	{
		for (std::size_t j = 0; j < this->queue.size(); j++)
		{
			//if it matches a basefunction, or user-defined function
			if ((this->method_list.count(command[i]) <= 0) || (this->queue[j].functionname.compare(command[i]) == 0) && (this->queue.size() != 0))
			{
				numberofoperators++;
				keeptrack[i] = i;
				this->queue[j].functionlocations.push_back(j);
			}
		}
	}
	std::vector<var> outputs;

	for (std::size_t i = 0; i < this->queue.size(); i++)	//running the functions
	{
		for (std::size_t j = 0; j < this->queue[i].functionlocations.size(); j++)
		{
			
		}
	}
	
	delete[] keeptrack;
	return outputs;
}

var Subroutine::run_method(Method& method, std::size_t& operatorlocation, std::vector<std::string>& command)
{

}