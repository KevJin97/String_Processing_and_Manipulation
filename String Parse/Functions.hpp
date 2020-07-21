#pragma once

#include <vector>
#include <map>
#include <utility>
#include <string>

#include "MethodTypes.hpp"

struct Functions
{
	std::vector<std::string> function_list;
	std::vector<std::string> queue;
	var output;

	bool isoperator(std::string op);	//checks if it's an operator
	std::vector<std::vector<int>> relativelocations(Method& method);	//returns the relative-to-operator locations of all inputs
};

bool Functions::isoperator(std::string op)
{
	if (this->function_list.size())
	{
		for (std::size_t i = 0; i < function_list.size(); i++)
		{
			if (function_list[i].compare(op))
			{
				return true;
			}
		}
	}
	else
	{
		return false;
	}
}

std::vector<std::vector<int>> Functions::relativelocations(Method& method)
{
	std::vector<std::vector<int>> returnvector;
	std::vector<int> relativelocation;
	std::size_t operatorlocation;

	for (std::size_t i = 0; i < method.syntax.size(); i++)	//find the operator
	{
		if (method.syntax[i].compare(method.name) == 0)
		{
			operatorlocation = i;
			break;
		}
	}
	for (std::size_t i = 0; i < method.syntax.size(); i++)	//find all locations of the variables
	{
		for (std::size_t j = 0; j < method.input.size(); j++)
		{
			if (method.input[j].varname.compare(method.syntax[i]) == 0)
			{
				relativelocation.push_back(i - operatorlocation);
			}
		}
		returnvector.push_back(relativelocation);
		relativelocation.clear();
	}

	return returnvector;
}