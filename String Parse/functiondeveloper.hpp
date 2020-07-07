#ifndef FUNCTIONDEVELOPER_HPP
#define FUNCTIONDEVELOPER_HPP

#include <cmath>
#include <string>
#include <vector>
#include "stringprocess.hpp"

struct var
{
	std::string varname;
	double value;
	std::string type;
	bool unknown;

	var();
	var(std::string data);
	var(double value);
	void operator=(var input);
	void operator=(std::string data);
};

var::var()
{ 
	this->value = 0;
	this->unknown = true;
}

var::var(std::string data)
{
	bool isnumber;
	for (std::size_t i = 0; i < data.size(); i++)
	{
		if (('0' <= data[i]) && (data[i] <= '9'))
		{
			isnumber = true;
		}
		else
		{
			isnumber = false;
			break;
		}
	}
	if (!isnumber)
	{
		this->varname = data;
		this->value = 0;	//unusuable if unknown false
		this->type = "double";
		this->unknown = false;
	}
	else
	{
		this->value = std::stod(data);
		this->type = "double";
		this->unknown = true;
	}
}

var::var(double value)
{
	this->varname = "num";
	this->value = value;
	this->type = "double";
	this->unknown = true;
}

void var::operator=(var input)
{
	this->varname = input.varname;
	this->value = input.value;
	this->type = input.type;
	this->unknown = input.unknown;
}

void var::operator=(std::string data)
{
	bool isnumber;
	for (std::size_t i = 0; i < data.size(); i++)
	{
		if (('0' <= data[i]) && (data[i] <= '9'))
		{
			isnumber = true;
		}
		else
		{
			isnumber = false;
			break;
		}
	}
	if (!isnumber)
	{
		this->varname = data;
		this->value = 0;	//unusuable if unknown false
		this->type = "double";
		this->unknown = false;
	}
	else
	{
		this->value = std::stod(data);
		this->type = "double";
		this->unknown = true;
	}
}


std::vector<std::size_t*> parenthesis_pairing(std::vector<std::size_t> open, std::vector<std::size_t> closed)	//read order of parenthesis, make sure to erase data later
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
		delete[] used;
	}
	else
	{
		//parenthesis aren't equal
	}
	return paired;
}


struct Method	//contains instruction set
{
	std::string name;
	std::vector<var> input;
	std::vector<std::string> syntax;
	std::vector<std::string> functiondef;
	var output;
	
	Method() {}
	void operator=(Method function);
};

void Method::operator=(Method function)
{
	this->name = function.name;
	this->input = function.input;
	this->syntax = function.syntax;
	this->functiondef = function.functiondef;
}


Method parenthesis(CommandString parsed, std::size_t open, std::size_t closed)	//don't access input
{
	Method parenthesis;
	parenthesis.name = "()";
	
	for (std::size_t i = open + 1; i < closed; i++)
	{
		parenthesis.syntax.push_back(parsed[i]);
		parenthesis.functiondef.push_back(parsed[i]);
	}
	return parenthesis;
}


namespace basefunctions
{
	//basic operators
	var power(var input1, var input2)
	{
		var ans("ans");

		if ((input1.unknown == true) && (input2.unknown == true))
		{
			ans.value = pow(input1.value, input2.value);
			ans.unknown = true;
		}
		return ans;
	}

	var multiply(var input1, var input2)
	{
		var ans("ans");

		if ((input1.unknown == true) && (input2.unknown == true))
		{
			ans.value = input1.value * input2.value;
			ans.unknown = true;
		}
		return ans;
	}

	var divide(var input1, var input2)
	{
		var ans("ans");

		if ((input1.unknown == true) && (input2.unknown == true))
		{
			ans.value = input1.value / input2.value;
			ans.unknown = true;
		}
		return ans;
	}

	var add(var input1, var input2)
	{
		var ans("ans");

		if ((input1.unknown == true) && (input2.unknown == true))
		{
			ans.value = input1.value + input2.value;
			ans.unknown = true;
		}
		return ans;
	}

	var subtract(var input1, var input2)
	{
		var ans("ans");

		if ((input1.unknown == true) && (input2.unknown == true))
		{
			ans.value = input1.value - input2.value;
			ans.unknown = true;
		}
		return ans;
	}

	var negative(var input)
	{
		var ans("ans");

		if (input.unknown == true)
		{
			ans.value = -input.value;
			ans.unknown = true;
		}
		return ans;
	}

	//functions
	var exponential(var input)
	{
		var ans("ans");

		if (input.unknown == true)
		{
			ans.value = exp(input.value);
			ans.unknown = true;
		}
		return ans;
	}

	var cosine(var input)
	{
		var ans("ans");

		if (input.unknown == true)
		{
			ans.value = cos(input.value);
			ans.unknown = true;
		}
		return ans;
	}

	var sine(var input)
	{
		var ans("ans");

		if (input.unknown == true)
		{
			ans.value = sin(input.value);
			ans.unknown = true;
		}
		return ans;
	}

	var tangent(var input)
	{
		var ans("ans");

		if (input.unknown == true)
		{
			ans.value = tan(input.value);
			ans.unknown = true;
		}
		return ans;
	}

	var arccosine(var input)
	{
		var ans("ans");

		if (input.unknown == true)
		{
			ans.value = acos(input.value);
			ans.unknown = true;
		}
		return ans;
	}

	var arcsine(var input)
	{
		var ans("ans");

		if (input.unknown == true)
		{
			ans.value = asin(input.value);
			ans.unknown = true;
		}
		return ans;
	}

	var arctangent(var input)
	{
		var ans("ans");

		if (input.unknown == true)
		{
			ans.value = atan(input.value);
			ans.unknown = true;
		}
		return ans;
	}

	var root(var base, var input)
	{
		var ans("ans");

		if ((base.unknown == true) && (input.unknown == true))
		{
			ans.value = pow(input.value, 1 / base.value);
			ans.unknown = true;
		}
		return ans;
	}

	var root(var input)	//default 2
	{
		return root(2, input);
	}

	var natural_logarithm(var input)
	{
		var ans("ans");

		if (input.unknown == true)
		{
			ans.value = log(input.value);
			ans.unknown = true;
		}
		return ans;
	}

	var logarithm(var base, var input)
	{
		var ans("ans");

		if ((base.unknown == true) && (input.unknown == true))
		{
			ans.value = log(input.value) / log(base.value);
			ans.unknown = true;
		}
		return ans;
	}

	var logarithm(var input)	//default 10
	{
		var ans("ans");

		if (input.unknown == true)
		{
			ans.value = log(input.value) / log(10);
			ans.unknown = true;
		}
		return ans;
	}

	Method function(std::string name, std::vector<var> inputs)
	{
		Method base;
		if ((name.compare("^") == 0) && (inputs.size() == 2))
		{
			base.name = name;
			base.input = inputs;
			base.syntax = { inputs[0].varname, "^", inputs[1].varname };
			base.functiondef = { inputs[0].varname, "^", inputs[1].varname };
			base.output = power(inputs[0], inputs[1]);
		}
		else if ((name.compare("*") == 0) && (inputs.size() == 2))
		{
			base.name = name;
			base.input = inputs;
			base.syntax = { inputs[0].varname, "*", inputs[1].varname };
			base.functiondef = { inputs[0].varname, "*", inputs[1].varname };
			base.output = multiply(inputs[0], inputs[1]);
		}
		else if ((name.compare("/") == 0) && (inputs.size() == 2))
		{
			base.name = name;
			base.input = inputs;
			base.syntax = { inputs[0].varname, "/", inputs[1].varname };
			base.functiondef = { inputs[0].varname, "/", inputs[1].varname };
			base.output = divide(inputs[0], inputs[1]);
		}
		else if ((name.compare("+") == 0) && (inputs.size() == 2))
		{
			base.name = name;
			base.input = inputs;
			base.syntax = { inputs[0].varname, "+", inputs[1].varname };
			base.functiondef = { inputs[0].varname, "+", inputs[1].varname };
			base.output = add(inputs[0], inputs[1]);
		}
		else if ((name.compare("-") == 0) && (inputs.size() == 2))
		{
			base.name = name;
			base.input = inputs;
			base.syntax = { inputs[0].varname, "-", inputs[1].varname };
			base.functiondef = { inputs[0].varname, "-", inputs[1].varname };
			base.output = subtract(inputs[0], inputs[1]);
		}
		else if ((name.compare("-") == 0) && (inputs.size() == 1))
		{
			base.name = name;
			base.input = inputs;
			base.syntax = { "-", inputs[0].varname };
			base.functiondef = { "-", inputs[0].varname };
			base.output = negative(inputs[0]);
		}
		else if ((name.compare("exp") == 0) && (inputs.size() == 1))
		{
			base.name = name;
			base.input = inputs;
			base.syntax = { "exp", "(", inputs[0].varname, ")" };
			base.functiondef = { "exp", "(", inputs[0].varname, ")" };
			base.output = exponential(inputs[0]);
		}
		else if ((name.compare("cos") == 0) && (inputs.size() == 1))
		{
			base.name = name;
			base.input = inputs;
			base.syntax = { "cos", "(", inputs[0].varname, ")" };
			base.functiondef = { "cos", "(", inputs[0].varname, ")" };
			base.output = cosine(inputs[0]);
		}
		else if ((name.compare("sin") == 0) && (inputs.size() == 1))
		{
			base.name = name;
			base.input = inputs;
			base.syntax = { "sin", "(", inputs[0].varname, ")" };
			base.functiondef = { "sin", "(", inputs[0].varname, ")" };
			base.output = sine(inputs[0]);
		}
		else if ((name.compare("tan") == 0) && (inputs.size() == 1))
		{
			base.name = name;
			base.input = inputs;
			base.syntax = { "tan", "(", inputs[0].varname, ")" };
			base.functiondef = { "tan", "(", inputs[0].varname, ")" };
			base.output = tangent(inputs[0]);
		}
		else if ((name.compare("acos") == 0) && (inputs.size() == 1))
		{
			base.name = name;
			base.input = inputs;
			base.syntax = { "acos", "(", inputs[0].varname, ")" };
			base.functiondef = { "acos", "(", inputs[0].varname, ")" };
			base.output = arccosine(inputs[0]);
		}
		else if ((name.compare("asin") == 0) && (inputs.size() == 1))
		{
			base.name = name;
			base.input = inputs;
			base.syntax = { "asin", "(", inputs[0].varname, ")" };
			base.functiondef = { "asin", "(", inputs[0].varname, ")" };
			base.output = arcsine(inputs[0]);
		}
		else if ((name.compare("atan") == 0) && (inputs.size() == 1))
		{
			base.name = name;
			base.input = inputs;
			base.syntax = { "atan", "(", inputs[0].varname, ")" };
			base.functiondef = { "atan", "(", inputs[0].varname, ")" };
			base.output = arctangent(inputs[0]);
		}
		else if ((name.compare("root") == 0) && (inputs.size() == 1))
		{
			base.name = name;
			base.input = inputs;
			base.syntax = { "root", "(", inputs[0].varname, ")" };
			base.functiondef = { "root", "(", inputs[0].varname, ")" };
			base.output = root(inputs[0]);
		}
		else if ((name.compare("root") == 0) && (inputs.size() == 2))
		{
			base.name = name;
			base.input = inputs;
			base.syntax = { "root", inputs[0].varname, "(", inputs[1].varname, ")" };
			base.functiondef = { "root", inputs[0].varname, "(", inputs[1].varname, ")" };
			base.output = root(inputs[0], inputs[1]);
		}
		else if ((name.compare("log") == 0) && (inputs.size() == 1))
		{
			base.name = name;
			base.input = inputs;
			base.syntax = { "log", "(", inputs[0].varname, ")" };
			base.functiondef = { "log", "(", inputs[0].varname, ")" };
			base.output = logarithm(inputs[0]);
		}
		else if ((name.compare("log") == 0) && (inputs.size() == 2))
		{
			base.name = name;
			base.input = inputs;
			base.syntax = { "log", inputs[0].varname, "(", inputs[1].varname, ")" };
			base.functiondef = { "log", inputs[0].varname, "(", inputs[1].varname, ")" };
			base.output = logarithm(inputs[0], inputs[1]);
		}
		else if ((name.compare("ln") == 0) && (inputs.size() == 1))
		{
			base.name = name;
			base.input = inputs;
			base.syntax = { "ln", "(", inputs[0].varname, ")" };
			base.functiondef = { "ln", "(", inputs[0].varname, ")" };
			base.output = logarithm(inputs[0]);
		}
		else
		{
			base.name = "NOFUNCTION";
			base.syntax = { "NOFUNCTION" };
			base.functiondef = { "NOFUNCTION" };
		}
		return base;
	}
}


class Subroutine
{
protected:
	Method function;
	std::vector<std::string> operator_list;
	std::vector<std::string> function_list;

public:
	Subroutine();

	void define(std::string functionname);	//can't handle multiple line commands yet
	Method return_method();
	Method basefunction(std::string functionname, std::vector<var> inputs);
	void set_operator_list(std::vector<std::string> list);
	var solve();
	var solve(CommandString command);
	bool checkfunction(Method function);	//check if defined function could be confused with a predefined function
	
	void operator=(Subroutine subroutine);

	//testcode
	void test()
	{
		CommandString check;
		std::cout << std::endl;
		std::cout << "FUNCTION (method)" << std::endl;
		std::cout << "Function name: " << function.name << std::endl;
		std::cout << "Input(s): "; for (std::size_t i = 0; i < function.input.size(); i++) { std::cout << function.input[i].varname << " "; } std::cout << std::endl;
		std::cout << "Syntax: " << check.back2string(function.syntax) << std::endl;
		std::cout << "Function Definition: " << check.back2string(function.functiondef) << std::endl;
	}
};

Subroutine::Subroutine()
{
	this->operator_list = 
	{
		"-", 
		"+", 
		"/", 
		"*", 
		"^", 
		"=",
		")",
		"("
	};
	this->function_list =
	{
		"exp",
		"cos",
		"sin",
		"tan",
		"log",
		"ln",
		"asin",
		"acos",
		"atan",
		"root",
	};
}

void Subroutine::define(std::string functionname)	//issues come up when functionname contains an operator. resolve later
{
	CommandString syntax;
	Method function;
	syntax.parse_at(this->operator_list);

	function.name = functionname;

	std::cout << "define syntax: ";
	syntax.getinput();	//define syntax, create error for when syntax definition doesn't have function name
	function.syntax = syntax.return_parsed();
	
	syntax.isolate(functionname);
	syntax.remove(functionname);	//filter functionname
	syntax.remove(this->operator_list);	//filter all operators

	for (std::size_t i = 0; i < syntax.size(); i++)
	{
		if (function.input.size() == 0)
		{
			function.input.push_back(syntax[i]);
		}
		else
		{
			for (std::size_t j = 0; j < function.input.size(); j++)	//make sure there's no duplicates
			{
				if (function.input[j].varname.compare(syntax[i]) != 0)
				{
					function.input.push_back(syntax[i]);
				}
			}
		}
	}
	std::cout << "function definition: ";
	syntax.getinput();	//for functiondef
	function.functiondef = syntax.return_parsed();	//work on string parser?

	if (!this->checkfunction(function))
	{
		this->function = function;
	}
	else
	{
		//error, function may already exist
	}
}

Method Subroutine::return_method()
{
	return this->function;
}

Method Subroutine::basefunction(std::string functionname, std::vector<var> inputs)
{
	Method function = basefunctions::function(functionname, inputs);
	return function;
}

void Subroutine::set_operator_list(std::vector<std::string> list)
{
	operator_list = list;
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
	Method base = this->basefunction(function.name, function.input);
	if (base.name == "NOFUNCTION")	//false if function doesn't exist
	{
		return false;
	}
	else
	{
		return true;
	}
}

void Subroutine::operator=(Subroutine subroutine)
{
	this->function = subroutine.return_method();
}

#endif