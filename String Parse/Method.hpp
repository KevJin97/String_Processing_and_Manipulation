#pragma once

#include <vector>
#include <string>
#include <map>
#include <utility>

#include "Var.hpp"

//TODO: base "Method" functions: 'loop()', 'array/list', '=', ','
//Perhaps different operator "overloads" for every data set? ...yeah, this is probably how building programming languages work

//Method only contains raw instructions for new functions being built
//Any inherited structs should contain basefunctions and operator instructions
struct Method
{
	std::string name;	//function name
	std::vector<var> input;	//list of inputs
	std::vector<std::string> syntax;	//the syntax of how it's used
	std::vector<std::string> functiondef;	//how to execute using basefunction list

	void operator=(Method function);
};

void Method::operator=(Method function)
{
	this->name = function.name;
	this->input = function.input;
	this->syntax = function.syntax;
	this->functiondef = function.functiondef;
}