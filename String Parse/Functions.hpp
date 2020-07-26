#pragma once

#include <vector>
#include <map>
#include <utility>
#include <string>

#include "MethodTypes.hpp"

struct Functions
{
	std::map<std::string, Method> method_list;	//holds syntax and variables
	std::vector<std::string> order;	//what order to execute 
	var output;

	bool isoperator(std::string op);	//checks if it's an operator

	inline void function(std::vector<std::string>& command, std::size_t& operatorlocation, std::vector<var*>& variables, var& output) {}	//define later
};

bool Functions::isoperator(std::string op)
{
	if (this->method_list.count(op) <= 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}