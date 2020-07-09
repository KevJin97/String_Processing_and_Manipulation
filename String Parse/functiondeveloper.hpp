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


struct Method	//contains instruction set
{
	std::vector<std::string> operator_list;

	std::string name;
	std::vector<var> input;
	std::vector<std::string> syntax;
	std::vector<std::string> functiondef;
	var output;
	
	Method();
	void operator=(Method function);
};

Method::Method()
{
	this->operator_list =
	{
		")",
		"("
	};
}

void Method::operator=(Method function)
{
	this->name = function.name;
	this->input = function.input;
	this->syntax = function.syntax;
	this->functiondef = function.functiondef;
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


struct MathMethod : public Method
{
	std::vector<std::string> function_list;

	MathMethod();
	//basic operators
	var power(var input1, var input2);
	var multiply(var input1, var input2);
	var divide(var input1, var input2);
	var add(var input1, var input2);
	var subtract(var input1, var input2);
	var negative(var input);
	//functions
	var exponential(var input);
	var cosine(var input);
	var sine(var input);
	var tangent(var input);
	var arccosine(var input);
	var arcsine(var input);
	var arctangent(var input);
	var root(var base, var input);
	var root(var input);	//default 2
	var natural_logarithm(var input);
	var logarithm(var base, var input);
	var logarithm(var input);	//default 10

	std::vector<Method> functions();	//possibly redesign this
};

MathMethod::MathMethod()
{
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
		"root"
	};
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
}

var MathMethod::power(var input1, var input2)
{
	var ans("ans");

	if ((input1.unknown == true) && (input2.unknown == true))
	{
		ans.value = pow(input1.value, input2.value);
		ans.unknown = true;
	}
	return ans;
}

var MathMethod::multiply(var input1, var input2)
{
	var ans("ans");

	if ((input1.unknown == true) && (input2.unknown == true))
	{
		ans.value = input1.value * input2.value;
		ans.unknown = true;
	}
	return ans;
}

var MathMethod::divide(var input1, var input2)
{
	var ans("ans");

	if ((input1.unknown == true) && (input2.unknown == true))
	{
		ans.value = input1.value / input2.value;
		ans.unknown = true;
	}
	return ans;
}

var MathMethod::add(var input1, var input2)
{
	var ans("ans");

	if ((input1.unknown == true) && (input2.unknown == true))
	{
		ans.value = input1.value + input2.value;
		ans.unknown = true;
	}
	return ans;
}

var MathMethod::subtract(var input1, var input2)
{
	var ans("ans");

	if ((input1.unknown == true) && (input2.unknown == true))
	{
		ans.value = input1.value - input2.value;
		ans.unknown = true;
	}
	return ans;
}

var MathMethod::negative(var input)
{
	var ans("ans");

	if (input.unknown == true)
	{
		ans.value = -input.value;
		ans.unknown = true;
	}
	return ans;
}

var MathMethod::exponential(var input)
{
	var ans("ans");

	if (input.unknown == true)
	{
		ans.value = exp(input.value);
		ans.unknown = true;
	}
	return ans;
}

var MathMethod::cosine(var input)
{
	var ans("ans");

	if (input.unknown == true)
	{
		ans.value = cos(input.value);
		ans.unknown = true;
	}
	return ans;
}

var MathMethod::sine(var input)
{
	var ans("ans");

	if (input.unknown == true)
	{
		ans.value = sin(input.value);
		ans.unknown = true;
	}
	return ans;
}

var MathMethod::tangent(var input)
{
	var ans("ans");

	if (input.unknown == true)
	{
		ans.value = tan(input.value);
		ans.unknown = true;
	}
	return ans;
}

var MathMethod::arccosine(var input)
{
	var ans("ans");

	if (input.unknown == true)
	{
		ans.value = acos(input.value);
		ans.unknown = true;
	}
	return ans;
}

var MathMethod::arcsine(var input)
{
	var ans("ans");

	if (input.unknown == true)
	{
		ans.value = asin(input.value);
		ans.unknown = true;
	}
	return ans;
}

var MathMethod::arctangent(var input)
{
	var ans("ans");

	if (input.unknown == true)
	{
		ans.value = atan(input.value);
		ans.unknown = true;
	}
	return ans;
}

var MathMethod::root(var base, var input)
{
	var ans("ans");

	if ((base.unknown == true) && (input.unknown == true))
	{
		ans.value = pow(input.value, 1 / base.value);
		ans.unknown = true;
	}
	return ans;
}

var MathMethod::root(var input)	//default 2
{
	return root(2, input);
}

var MathMethod::natural_logarithm(var input)
{
	var ans("ans");

	if (input.unknown == true)
	{
		ans.value = log(input.value);
		ans.unknown = true;
	}
	return ans;
}

var MathMethod::logarithm(var base, var input)
{
	var ans("ans");

	if ((base.unknown == true) && (input.unknown == true))
	{
		ans.value = log(input.value) / log(base.value);
		ans.unknown = true;
	}
	return ans;
}

var MathMethod::logarithm(var input)	//default 10
{
	var ans("ans");

	if (input.unknown == true)
	{
		ans.value = log(input.value) / log(10);
		ans.unknown = true;
	}
	return ans;
}

std::vector<Method> MathMethod::functions()
{
	Method base;
	std::vector<Method> functions;
	
	std::vector<var> inputs;
	inputs[0] = "var1";
	inputs[1] = "var2";

	base.name = "^";
	base.input = inputs;
	base.syntax = { inputs[0].varname, "^", inputs[1].varname };
	base.functiondef = { inputs[0].varname, "^", inputs[1].varname };
	base.output = power(inputs[0], inputs[1]);
	
	functions.push_back(base);
		
	base.name = "*";
	base.input = inputs;
	base.syntax = { inputs[0].varname, "*", inputs[1].varname };
	base.functiondef = { inputs[0].varname, "*", inputs[1].varname };
	base.output = multiply(inputs[0], inputs[1]);
	
	functions.push_back(base);

	base.name = "/";
	base.input = inputs;
	base.syntax = { inputs[0].varname, "/", inputs[1].varname };
	base.functiondef = { inputs[0].varname, "/", inputs[1].varname };
	base.output = divide(inputs[0], inputs[1]);
	
	functions.push_back(base);

	base.name = "+";
	base.input = inputs;
	base.syntax = { inputs[0].varname, "+", inputs[1].varname };
	base.functiondef = { inputs[0].varname, "+", inputs[1].varname };
	base.output = add(inputs[0], inputs[1]);

	functions.push_back(base);

	base.name = "-";
	base.input = inputs;
	base.syntax = { inputs[0].varname, "-", inputs[1].varname };
	base.functiondef = { inputs[0].varname, "-", inputs[1].varname };
	base.output = subtract(inputs[0], inputs[1]);
	
	functions.push_back(base);

	base.name = "-";
	base.input = inputs;
	base.syntax = { "-", inputs[0].varname };
	base.functiondef = { "-", inputs[0].varname };
	base.output = negative(inputs[0]);
	
	functions.push_back(base);
	base.name = "exp";
	base.input = inputs;
	base.syntax = { "exp", "(", inputs[0].varname, ")" };
	base.functiondef = { "exp", "(", inputs[0].varname, ")" };
	base.output = exponential(inputs[0]);
	
	functions.push_back(base);

	base.name = "cos";
	base.input = inputs;
	base.syntax = { "cos", "(", inputs[0].varname, ")" };
	base.functiondef = { "cos", "(", inputs[0].varname, ")" };
	base.output = cosine(inputs[0]);
	
	functions.push_back(base);

	base.name = "sin";
	base.input = inputs;
	base.syntax = { "sin", "(", inputs[0].varname, ")" };
	base.functiondef = { "sin", "(", inputs[0].varname, ")" };
	base.output = sine(inputs[0]);
	
	functions.push_back(base);

	base.name = "tan";
	base.input = inputs;
	base.syntax = { "tan", "(", inputs[0].varname, ")" };
	base.functiondef = { "tan", "(", inputs[0].varname, ")" };
	base.output = tangent(inputs[0]);
	
	functions.push_back(base);

	base.name = "acos";
	base.input = inputs;
	base.syntax = { "acos", "(", inputs[0].varname, ")" };
	base.functiondef = { "acos", "(", inputs[0].varname, ")" };
	base.output = arccosine(inputs[0]);

	functions.push_back(base);

	base.name = "asin";
	base.input = inputs;
	base.syntax = { "asin", "(", inputs[0].varname, ")" };
	base.functiondef = { "asin", "(", inputs[0].varname, ")" };
	base.output = arcsine(inputs[0]);
	
	functions.push_back(base);

	base.name = "atan";
	base.input = inputs;
	base.syntax = { "atan", "(", inputs[0].varname, ")" };
	base.functiondef = { "atan", "(", inputs[0].varname, ")" };
	base.output = arctangent(inputs[0]);
	
	functions.push_back(base);

	base.name = "root";
	base.input = inputs;
	base.syntax = { "root", "(", inputs[0].varname, ")" };
	base.functiondef = { "root", "(", inputs[0].varname, ")" };
	base.output = root(inputs[0]);
	
	functions.push_back(base);

	base.name = "root";
	base.input = inputs;
	base.syntax = { "root", inputs[0].varname, "(", inputs[1].varname, ")" };
	base.functiondef = { "root", inputs[0].varname, "(", inputs[1].varname, ")" };
	base.output = root(inputs[0], inputs[1]);
	
	functions.push_back(base);

	base.name = "log";
	base.input = inputs;
	base.syntax = { "log", "(", inputs[0].varname, ")" };
	base.functiondef = { "log", "(", inputs[0].varname, ")" };
	base.output = logarithm(inputs[0]);
	
	functions.push_back(base);

	base.name = "log";
	base.input = inputs;
	base.syntax = { "log", inputs[0].varname, "(", inputs[1].varname, ")" };
	base.functiondef = { "log", inputs[0].varname, "(", inputs[1].varname, ")" };
	base.output = logarithm(inputs[0], inputs[1]);
	
	functions.push_back(base);

	base.name = "ln";
	base.input = inputs;
	base.syntax = { "ln", "(", inputs[0].varname, ")" };
	base.functiondef = { "ln", "(", inputs[0].varname, ")" };
	base.output = logarithm(inputs[0]);

	functions.push_back(base);

	return functions;
}


class Subroutine
{
protected:
	Method function;
	Method* base;

public:
	Subroutine();	//sets to default Method base
	Subroutine(Method* basemethod);	//new constructor for different types of Methods
	~Subroutine();	//delete memory from base

	void define(std::string functionname);	//can't handle multiple line commands yet
	Method return_method();
	std::size_t basefunction(std::string functionname, std::vector<var> inputs);	//returns the index the base function is located at
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
{	//temporary until MathString is finished
	base = new MathMethod;
	//base = new Method;	//replace with this
}

Subroutine::Subroutine(Method* basemethod)
{
	base = basemethod;
}

Subroutine::~Subroutine()
{
	delete base;
}

void Subroutine::define(std::string functionname)	//issues come up when functionname contains an operator. resolve later
{
	CommandString syntax;
	Method function;
	
	if (this->base->operator_list.size() != 0)
	{
		syntax.parse_at(this->base->operator_list);
	}

	function.name = functionname;

	std::cout << "define syntax: ";
	syntax.getinput();	//define syntax, create error for when syntax definition doesn't have function name
	function.syntax = syntax.return_parsed();
	
	syntax.isolate(functionname);
	syntax.remove(functionname);	//filter functionname
	
	if (this->base->operator_list.size() != 0)
	{
		syntax.remove(this->base->operator_list);	//filter all operators
	}

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

std::size_t Subroutine::basefunction(std::string functionname, std::vector<var> inputs)
{
	std::size_t index;

	for (index = 0; index < this->basefunction_list.size(); index++)
	{
		if ((functionname.compare(this->basefunction_list[index].name)) == 0 && (inputs.size() == this->basefunction_list[index].input.size()))
		{
			return index;
		}
	}

	return this->basefunction_list.size();	//return the size value (index is outside of the range)
}

void Subroutine::set_operator_list(std::vector<std::string> list)	//is this needed?
{
	this->base->operator_list = list;
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
	if (this->basefunction(function.name, function.input) == this->basefunction_list.size())	//false if function doesn't exist
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