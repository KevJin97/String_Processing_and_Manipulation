#include <vector>
#include <string>
#include <map>
#include <utility>
#include "VariableClass.cpp"

//TODO: base "Method" functions: 'loop()', 'array/list', '=', ','
//Perhaps different operator "overloads" for every data set? ...yeah, this is probably how building programming languages work

//Method only contains raw instructions for new functions being built
//Any inherited structs should contain basefunctions and operator instructions
class Method
{
protected:
	std::vector<std::string> function_list;

	std::string name;	//function name
	std::vector<var> input;	//list of inputs
	std::vector<std::string> syntax;	//the syntax of how it's used
	std::vector<std::string> functiondef;	//how to execute using basefunction list
	var output;

public:
	Method();

	void define(std::string functionname);	//define Method. Can't handle multiple lines
	void set_name(std::string name);	//set the name
	void set_input(std::vector<var> input);	//set input list
	void set_syntax(std::vector<std::string> syntax);	//set the syntax
	void set_functiondef(std::vector<std::string> functiondef);	//set the function definition
	Method return_Method();	//return the Method values
	
	virtual std::vector<Method> functions() {}	//TODO: remove this later
	void operator=(Method function);
};

Method::Method()
{
	this->function_list =
	{
		")",
		"("
	};

	this->output = "NA";
}

void Method::define(std::string functionname)
{
	CommandString syntax;
	syntax.parse_at(this->function_list);

	this->name = functionname;	//set function name

	std::cout << "Syntax Definition: ";
	syntax.getinput();
	this->syntax = syntax.return_parsed();	//set function syntax

	syntax.ignore(this->function_list);
	syntax.ignore(functionname);	//this is inefficient
	for (std::size_t i = 0; i < syntax.size(); i++)	//set inputs
	{
		if (this->input.size() == 0)
		{
			this->input.push_back(syntax[i]);
		}
		else
		{
			for (std::size_t j = 0; j < this->input.size(); j++)
			{
				if (syntax[i].compare(this->input[j].varname) != 0)
				{
					this->input.push_back(syntax[i]);
				}
			}
		}
	}

	syntax.reset_ignore();
	std::cout << "Function Definition: ";
	syntax.getinput();
	this->functiondef = syntax.return_parsed();	//set function definition
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

Method Method::return_Method()
{
	return *this;
}

void Method::operator=(Method function)
{
	this->name = function.name;
	this->input = function.input;
	this->syntax = function.syntax;
	this->functiondef = function.functiondef;
}