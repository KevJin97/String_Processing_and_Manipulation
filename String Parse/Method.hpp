#pragma once

#include <vector>
#include <string>
#include <map>
#include <utility>

#include "Var.hpp"

//Method only contains raw instructions for new functions being built
//Any inherited structs should contain basefunctions and operator instructions
//TODO: implement an error for variables that aren't used
struct Method
{
	std::string name;	//function name
	std::vector<var*> input;	//list of inputs
	std::vector<std::string> syntax;	//the syntax of how it's used
	std::vector<std::string> functiondef;	//how to execute using basefunction list
	
	std::vector<int> relativelocations;	//relative-to-operator locations of all inputs, each input can only be entered once
	std::size_t operatorlocation;	//location of operator in syntax

	void setrelative();	//set relative location
	void clear();	//clear all components
	void wipe();	//clear with deallocation

	void operator=(Method function);
};

void Method::setrelative()
{
	if (relativelocations.size() != 0)
	{
		relativelocations.clear();
	}

	this->operatorlocation = this->syntax.size();

	for (std::size_t i = 0; i < this->syntax.size(); i++)	//find the operator
	{
		if (this->syntax[i].compare(this->name) == 0)
		{
			this->operatorlocation = i;
			break;
		}
	}
	if (this->operatorlocation != this->syntax.size())	//if operator is in syntax
	{
		bool* hasbeenused = new bool[this->input.size()];
		for (std::size_t i = 0; i < this->input.size(); i++)	//initialize hasbeenused
		{
			hasbeenused[i] = false;
		}

		for (std::size_t i = 0; i < this->input.size(); i++)	//find all locations of the variables
		{
			for (std::size_t j = 0; j < this->syntax.size(); j++)
			{
				if (this->input[i]->varname.compare(this->syntax[j]) == 0)
				{
					this->relativelocations.push_back(j - this->operatorlocation);
					hasbeenused[i] = true;
					break;
				}
			}
		}
		if (this->relativelocations.size() != this->input.size())	//warning message
		{
			std::cout << "WARNING: NOT ALL VARIABLES WERE USED" << std::endl;
			std::vector<std::string> hold;

			for (std::size_t i = 0; i < this->input.size(); i++)	//remove the unused vector
			{
				if (hasbeenused[i])
				{
					hold.push_back(this->input[i]->varname);
				}
			}
		}
		delete[] hasbeenused;
	}
	else
	{
		std::cout << "Function name was not used in the syntax" << std::endl;	//error message
	}
}

void Method::clear()
{
	this->name.clear();
	this->input.clear();
	this->syntax.clear();
	this->functiondef.clear();
	this->relativelocations.clear();
}

void Method::wipe()
{
	for (std::size_t i = 0; i < this->input.size(); i++)
	{
		delete this->input[i];
	}
	this->input.clear();
	this->syntax.clear();
	this->functiondef.clear();
	this->relativelocations.clear();
}

void Method::operator=(Method function)
{
	this->clear();
	this->name = function.name;
	for (std::size_t i = 0; i < function.input.size(); i++)
	{
		this->input.push_back(new var(function.input[i]->varname));
	}
	this->syntax = function.syntax;
	this->functiondef = function.functiondef;
	this->setrelative();
}