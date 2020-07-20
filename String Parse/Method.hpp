#pragma once

#include <vector>
#include <string>
#include <map>
#include <utility>

#include "VariableClass.hpp"

//TODO: base "Method" functions: 'loop()', 'array/list', '=', ','
//Perhaps different operator "overloads" for every data set? ...yeah, this is probably how building programming languages work

//Method only contains raw instructions for new functions being built
//Any inherited structs should contain basefunctions and operator instructions
class Method
{
private:
	std::map<std::string, var(Method::*)(std::vector<var>&)> basefunctions;

protected:
	std::map<std::string, Method> basemethods;	//map the methods

	std::vector<std::string> function_list;
	std::vector<std::string> queue;

	std::string name;	//function name
	std::vector<var> input;	//list of inputs
	std::vector<std::string> syntax;	//the syntax of how it's used
	std::vector<std::string> functiondef;	//how to execute using basefunction list

	std::vector<std::vector<int>> relative_input_location;	//input location relative to operator location in syntax
	std::size_t operator_location;	//location of operator in syntax

public:
	Method();

	void define(std::string& functionname, std::vector<std::string>& syntax, std::vector<std::string>& functiondef);	//define Method. Can't handle multiple lines
	void set_name(std::string name);	//set the name
	void set_input(std::vector<var> input);	//set input list
	void set_syntax(std::vector<std::string> syntax);	//set the syntax
	void set_functiondef(std::vector<std::string> functiondef);	//set the function definition
	void set_relative();	//set relative locations in syntax
	bool isoperator(std::string input);	//check if inputted string has an operator tied to it (function_list)

	void equate(std::vector<var>& inputs);	//setting variables equal
	
	std::string return_name();
	std::vector<var> return_input();
	std::vector<std::string> return_syntax();
	std::vector<std::string> return_functiondef();
	
	std::size_t return_operator();	//return operator_location
	std::vector<std::string> return_queue();	//return the queue... may be rewritten later

	virtual std::map<std::string, Method>* return_Method();	//returns mapped methods
	virtual var functions(std::string& functionname, std::vector<var>& input);	//parse through to give function result. this will be removed later for map implementation

	void operator=(Method function);
};

Method::Method()
{
	this->function_list =
	{
		")",
		"("
	};
}

void Method::define(std::string& name, std::vector<std::string>& syntax, std::vector<std::string>& functiondef)
{
	this->name = name;	//set function name
	this->syntax = syntax;	//set function syntax

	for (std::size_t i = 0; i < syntax.size(); i++)	//set inputs
	{
		if ((this->input.size() == 0) && (this->syntax[i].compare(name) != 0))
		{
			this->input.push_back(syntax[i]);
		}
		else
		{
			for (std::size_t j = 0; j < this->input.size(); j++)	//check to make sure variable isn't on list
			{
				if ((syntax[i].compare(this->input[j].varname) != 0) && (this->syntax[i].compare(name) != 0))
				{
					this->input.push_back(syntax[i]);
				}
			}
		}
	}

	this->functiondef = functiondef;	//set function definition

	this->set_relative();
}

void Method::set_name(std::string name)
{
	this->name = name;
}

void Method::set_input(std::vector<var> input)
{
	this->input = input;
}

void Method::set_syntax(std::vector<std::string> syntax)
{
	this->syntax = syntax;
}

void Method::set_functiondef(std::vector<std::string> functiondef)
{
	this->functiondef = functiondef;
}

void Method::set_relative()
{
	for (std::size_t i = 0; i < syntax.size(); i++)	//set operator_location
	{
		if (name.compare(syntax[i]) == 0)
		{
			this->operator_location = i;
			break;
		}
	}
	for (std::size_t i = 0; i < input.size(); i++)	//set relative_input_location
	{
		std::vector<int> hold;
		for (std::size_t j = 0; j < syntax.size(); j++)
		{
			if (syntax[j].compare(input[i].varname) == 0)
			{
				hold.push_back(j - this->operator_location);
			}
		}
		this->relative_input_location.push_back(hold);
	}
}

bool Method::isoperator(std::string input)
{
	for (std::size_t index = 0; index < this->function_list.size(); index++)
	{
		if (this->function_list[index].compare(input) == 0)
		{
			return true;
		}
	}
	return false;
}

void Method::equate(std::vector<var>& inputs)
{
	if (inputs.size() == 2)
	{
		inputs[0] = inputs[1];
	}
	else
	{
		//print too many input error message
	}
}

std::string Method::return_name()
{
	return this->name;
}

std::vector<var> Method::return_input()
{
	return this->input;
}

std::vector<std::string> Method::return_syntax()
{
	return this->syntax;
}

std::vector<std::string> Method::return_functiondef()
{
	return this->functiondef;
}

std::size_t Method::return_operator()
{
	return this->operator_location;
}

std::vector<std::string> Method::return_queue()
{
	return this->queue;
}

std::map<std::string, Method>* Method::return_Method()
{
	return &(this->basemethods);
}

var Method::functions(std::string& functionname, std::vector<var>& input)
{
	var ans;
	ans.varname = "ans";

	if (functionname.compare("=") == 0)
	{
		this->equate(input);
	}
	else
	{
		ans.varname = "NA";
	}
	return ans;
}

void Method::operator=(Method function)
{
	this->name = function.name;
	this->input = function.input;
	this->syntax = function.syntax;
	this->functiondef = function.functiondef;
}