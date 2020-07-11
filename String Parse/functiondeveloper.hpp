#ifndef FUNCTIONDEVELOPER_HPP
#define FUNCTIONDEVELOPER_HPP

#include <cmath>
#include <string>
#include <vector>
#include <map>
#include <utility>
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

	bool isnumber(std::string& data);

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
	if (!this->isnumber(data))
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

bool var::isnumber(std::string& data)
{
	if (data.size() > 0)
	{
		for (std::size_t i = 0; i < data.size(); i++)
		{
			if (('0' > data[i]) || (data[i] > '9'))
			{
				return false;
			}
			else
			{
				break;
			}
		}
		return true;
	}
	else
	{
		return false;
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
	if (!this->isnumber(data))
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

//TODO: base "Method" functions: 'loop()', 'array/list', '=', ','
//Perhaps different operator "overloads" for every data set? ...yeah, this is probably how building programming languages work

//Method only contains raw instructions for new functions being built
//Any inherited structs should contain basefunctions and operator instructions
struct Method
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

	this->output = "NA";
}

void Method::operator=(Method function)
{
	this->name = function.name;
	this->input = function.input;
	this->syntax = function.syntax;
	this->functiondef = function.functiondef;
}


std::vector<std::size_t*> parenthesis_pairing(std::vector<std::size_t> open, std::vector<std::size_t> closed)	//read order of parenthesis, make sure to erase data later, redesign?
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


//TODO: consider: '>', '<', '>=', '<=', '==', '!='
struct MathMethod : public Method
{
	std::vector<std::string> function_list;
	std::vector<var> inputs;
	
	std::map<std::string, var(MathMethod::*)(std::vector<var>&)> basefunction;
	//create map for methods maybe

	MathMethod();

	//basic operators
	var power(std::vector<var>& inputs);
	var multiply(std::vector<var>& inputs);
	var divide(std::vector<var>& inputs);
	var add(std::vector<var>& inputs);
	var subtract(std::vector<var>& inputs);
	//functions
	var exponential(std::vector<var>& inputs);
	var cosine(std::vector<var>& inputs);
	var sine(std::vector<var>& inputs);
	var tangent(std::vector<var>& inputs);
	var root(std::vector<var>& inputs);
	var natural_logarithm(std::vector<var>& inputs);
	var logarithm(std::vector<var>& inputs);

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
		"root",
		"-",
		"+",
		"/",
		"*",
		"^",
		"=",
		")",
		"("
	};
	
	//mapping all member functions	TODO: add parenthesis and comma
	basefunction.insert(std::pair<std::string, var(MathMethod::*)(std::vector<var>&)>("^", &MathMethod::power));
	basefunction.insert(std::pair<std::string, var(MathMethod::*)(std::vector<var>&)>("*", &MathMethod::multiply));
	basefunction.insert(std::pair<std::string, var(MathMethod::*)(std::vector<var>&)>("+", &MathMethod::add));
	basefunction.insert(std::pair<std::string, var(MathMethod::*)(std::vector<var>&)>("-", &MathMethod::subtract));
	basefunction.insert(std::pair<std::string, var(MathMethod::*)(std::vector<var>&)>("exp", &MathMethod::exponential));
	basefunction.insert(std::pair<std::string, var(MathMethod::*)(std::vector<var>&)>("cos", &MathMethod::cosine));
	basefunction.insert(std::pair<std::string, var(MathMethod::*)(std::vector<var>&)>("sin", &MathMethod::sine));
	basefunction.insert(std::pair<std::string, var(MathMethod::*)(std::vector<var>&)>("tan", &MathMethod::tangent));
	basefunction.insert(std::pair<std::string, var(MathMethod::*)(std::vector<var>&)>("root", &MathMethod::root));
	basefunction.insert(std::pair<std::string, var(MathMethod::*)(std::vector<var>&)>("ln", &MathMethod::natural_logarithm));
	basefunction.insert(std::pair<std::string, var(MathMethod::*)(std::vector<var>&)>("log", &MathMethod::logarithm));
}

var MathMethod::power(std::vector<var>& inputs)
{
	var ans("ans");
	
	if (inputs.size() == 2)
	{
		if ((inputs[0].unknown == true) && (inputs[1].unknown == true))
		{
			ans.value = pow(inputs[0].value, inputs[1].value);
			ans.unknown = true;
		}
	}
	return ans;
}

var MathMethod::multiply(std::vector<var>& inputs)
{
	var ans("ans");

	if (inputs.size() == 2)
	{
		if ((inputs[0].unknown == true) && (inputs[1].unknown == true))
		{
			ans.value = inputs[0].value * inputs[1].value;
			ans.unknown = true;
		}
	}
	return ans;
}

var MathMethod::divide(std::vector<var>& inputs)
{
	var ans("ans");

	if (inputs.size() == 2)
	{
		if ((inputs[0].unknown == true) && (inputs[1].unknown == true))
		{
			ans.value = inputs[0].value / inputs[1].value;
			ans.unknown = true;
		}
	}
	return ans;
}

var MathMethod::add(std::vector<var>& inputs)
{
	var ans("ans");

	if (inputs.size() == 2)
	{
		if ((inputs[0].unknown == true) && (inputs[1].unknown == true))
		{
			ans.value = inputs[0].value + inputs[1].value;
			ans.unknown = true;
		}
	}
	return ans;
}

var MathMethod::subtract(std::vector<var>& inputs)
{
	var ans("ans");

	if (inputs.size() == 2)
	{
		if ((inputs[0].unknown == true) && (inputs[1].unknown == true))
		{
			ans.value = inputs[0].value - inputs[1].value;
			ans.unknown = true;
		}
	}
	else if (inputs.size() == 1)	//negative if only one input
	{
		if (inputs[0].unknown == true)
		{
			ans.value = -inputs[0].value;
			ans.unknown = true;
		}
	}
	return ans;
}

var MathMethod::exponential(std::vector<var>& inputs)
{
	var ans("ans");
	
	if (inputs.size() == 1)
	{
		if (inputs[0].unknown == true)
		{
			ans.value = exp(inputs[0].value);
			ans.unknown = true;
		}
	}
	return ans;
}

var MathMethod::cosine(std::vector<var>& inputs)
{
	var ans("ans");

	if (inputs.size() == 1)
	{
		if (inputs[0].unknown == true)
		{
			ans.value = cos(inputs[0].value);
			ans.unknown = true;
		}
	}
	else if (inputs.size() == 2)	//arccosine
	{
		if (inputs[1].unknown == true)
		{
			ans.value = acos(inputs[1].value);
			ans.unknown = true;
		}
	}
	return ans;
}

var MathMethod::sine(std::vector<var>& inputs)
{
	var ans("ans");

	if (inputs.size() == 1)
	{
		if (inputs[0].unknown == true)
		{
			ans.value = sin(inputs[0].value);
			ans.unknown = true;
		}
	}
	else if (inputs.size() == 2)	//arcsine
	{
		if (inputs[1].unknown == true)
		{
			ans.value = acos(inputs[1].value);
			ans.unknown = true;
		}
	}
	return ans;
}

var MathMethod::tangent(std::vector<var>& inputs)
{
	var ans("ans");

	if (inputs.size() == 1)
	{
		if (inputs[0].unknown == true)
		{
			ans.value = tan(inputs[0].value);
			ans.unknown = true;
		}
	}
	else if (inputs.size() == 2)	//arctangent
	{
		if (inputs[1].unknown == true)
		{
			ans.value = atan(inputs[1].value);
			ans.unknown = true;
		}
	}
	return ans;
}

var MathMethod::root(std::vector<var>& inputs)
{
	var ans("ans");

	if (inputs.size() == 1)		//default 2
	{
		if (inputs[0].unknown == true)
		{
			ans.value = pow(inputs[1].value, 1 / inputs[0].value);
			ans.unknown = true;
		}
	}
	else if (inputs.size() == 2)	//(base, input)
	{
		if ((inputs[0].unknown == true) && (inputs[1].unknown == true))
		{
			ans.value = pow(inputs[1].value, 1 / base[0].value);
			ans.unknown = true;
		}
	}
	return ans;
}

var MathMethod::natural_logarithm(std::vector<var>& inputs)
{
	var ans("ans");
	if (inputs.size() == 1)
	{
		if (inputs[0].unknown == true)
		{
			ans.value = log(inputs[0].value);
			ans.unknown = true;
		}
	}
	return ans;
}

var MathMethod::logarithm(std::vector<var>& inputs)
{
	var ans("ans");
	
	if (inputs.size() == 1)	//default 10
	{
		if (input.unknown == true)
		{
			ans.value = log(inputs[0].value) / log(10);
			ans.unknown = true;
		}
	}
	else if (inputs.size() == 2)
	{
		if ((base.unknown == true) && (input.unknown == true))
		{
			ans.value = log(inputs[0].value) / log(inputs[1].value);
			ans.unknown = true;
		}
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
	base.output = natural_logarithm(inputs[0]);

	functions.push_back(base);

	return functions;
}


//TODO: create a natural language subroutine that inherits from this one
//Subroutine takes instruction sets in Method and processes it
class Subroutine
{
protected:
	Method* function;

public:
	Subroutine();	//sets to default Method base
	Subroutine(Method* basemethod);	//new constructor for different types of Methods
	~Subroutine();	//delete memory from base

	void define(std::string functionname);	//can't handle multiple line commands yet. Might move to inherited CommandString
	Method* return_method();
	std::size_t basefunction(std::string functionname, std::vector<var> inputs);	//returns the index the base function is located at
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
		std::cout << "Function name: " << function->name << std::endl;
		std::cout << "Input(s): "; for (std::size_t i = 0; i < function->input.size(); i++) { std::cout << function->input[i].varname << " "; } std::cout << std::endl;
		std::cout << "Syntax: " << check.back2string(function->syntax) << std::endl;
		std::cout << "Function Definition: " << check.back2string(function->functiondef) << std::endl;
	}
};

Subroutine::Subroutine()
{	//temporary until MathString is finished
	this->function = new MathMethod;
	//base = new Method;	//replace with this
}

Subroutine::Subroutine(Method* basemethod)
{
	this->function = basemethod;
}

Subroutine::~Subroutine()
{
	delete function;
}

void Subroutine::define(std::string functionname)	//issues come up when functionname contains an operator. resolve later
{
	CommandString syntax;
	Method function;
	
	if (this->function->operator_list.size() != 0)
	{
		syntax.parse_at(this->function->operator_list);
	}

	function.name = functionname;

	std::cout << "define syntax: ";
	syntax.getinput();	//define syntax, create error for when syntax definition doesn't have function name
	function.syntax = syntax.return_parsed();
	
	syntax.isolate(functionname);
	syntax.remove(functionname);	//filter functionname
	
	if (this->function->operator_list.size() != 0)
	{
		syntax.remove(this->function->operator_list);	//filter all operators
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
		*(this->function) = function;
	}
	else
	{
		//error, function may already exist
	}
}

Method* Subroutine::return_method()
{
	return this->function;
}

std::size_t Subroutine::basefunction(std::string functionname, std::vector<var> inputs)
{
	/*
	std::size_t index;

	for (index = 0; index < this->basefunction_list.size(); index++)
	{
		if ((functionname.compare(this->basefunction_list[index].name)) == 0 && (inputs.size() == this->basefunction_list[index].input.size()))
		{
			return index;
		}
	}

	return this->basefunction_list.size();	//return the size value (index is outside of the range)
	*/
	return 0;
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

void parenthesis(CommandString& parsed, std::size_t open, std::size_t close)
{
	
}

void Subroutine::operator=(Subroutine subroutine)
{
	delete function;
	this->function = subroutine.return_method();
}

#endif