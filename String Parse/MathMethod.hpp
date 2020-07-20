#pragma once

#include "VariableClass.hpp"
#include "Method.hpp"

//TODO: consider: '>', '<', '>=', '<=', '==', '!='
class MathMethod : public Method
{
private:
	std::map<std::string, var(MathMethod::*)(std::vector<var>&)> basefunctions;

protected:
	//basic operators
	//Method parenthesis(std::vector<std::string> parsed, std::size_t open, std::size_t close);
	virtual var power(std::vector<var>& inputs);
	virtual var multiply(std::vector<var>& inputs);
	virtual var divide(std::vector<var>& inputs);
	virtual var add(std::vector<var>& inputs);
	virtual var subtract(std::vector<var>& inputs);
	//functions
	virtual var exponential(std::vector<var>& inputs);
	virtual var cosine(std::vector<var>& inputs);
	virtual var sine(std::vector<var>& inputs);
	virtual var tangent(std::vector<var>& inputs);
	virtual var arccosine(std::vector<var>& inputs);
	virtual var arcsine(std::vector<var>& inputs);
	virtual var arctangent(std::vector<var>& inputs);
	virtual var root(std::vector<var>& inputs);
	virtual var natural_logarithm(std::vector<var>& inputs);
	virtual var logarithm(std::vector<var>& inputs);

public:
	MathMethod();
	
	std::map<std::string, Method>* return_Method();	//returns mapped methods
	var functions(std::string functionname);	//return the function result
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

	this->queue =
	{
		"exp",
		"cos",
		"sin",
		"tan",
		"ln",
		"log",
		")",
		"(",
		"^",
		"*",
		"/",
		"+",
		"-"
	};

	Method method;

	method.set_name("^");
	method.set_input({ "var1", "var2" });
	method.set_syntax({ "var1", "^", "var2" });
	method.set_functiondef({ "var1", "^", "var2" });
	method.set_relative();
	basemethods.insert(std::pair<std::string, Method >("^", method));

	method.set_name("*");
	method.set_input({ "var1", "var2" });
	method.set_syntax({ "var1", "*", "var2" });
	method.set_functiondef({ "var1", "*", "var2" });
	method.set_relative();
	basemethods.insert(std::pair<std::string, Method >("*", method));
	
	method.set_name("+");
	method.set_input({ "var1", "var2" });
	method.set_syntax({ "var1", "+", "var2" });
	method.set_functiondef({ "var1", "+", "var2" });
	method.set_relative();
	basemethods.insert(std::pair<std::string, Method >("+", method));

	method.set_name("-");
	method.set_input({ "var1", "var2" });
	method.set_syntax({ "var1", "-", "var2" });
	method.set_functiondef({ "var1", "-", "var2" });
	method.set_relative();
	basemethods.insert(std::pair<std::string, Method >("-", method));
	
	method.set_name("exp");
	method.set_input({ (var)"var" });
	method.set_syntax({ "exp", "(", "var", ")" });
	method.set_functiondef({ "exp", "(", "var", ")" });
	method.set_relative();
	basemethods.insert(std::pair<std::string, Method >("exp", method));
	
	method.set_name("cos");
	method.set_input({ (var)"var" });
	method.set_syntax({ "cos", "(", "var", ")" });
	method.set_functiondef({ "cos", "(", "var", ")" });
	method.set_relative();
	basemethods.insert(std::pair<std::string, Method >("cos", method));
	
	method.set_name("sin");
	method.set_input({ (var)"var" });
	method.set_syntax({ "sin", "(", "var", ")" });
	method.set_functiondef({ "sin", "(", "var", ")" });
	method.set_relative();
	basemethods.insert(std::pair<std::string, Method >("sin", method));
	
	method.set_name("tan");
	method.set_input({ (var)"var" });
	method.set_syntax({ "tan", "(", "var", ")" });
	method.set_functiondef({ "tan", "(", "var", ")" });
	method.set_relative();
	basemethods.insert(std::pair<std::string, Method >("tan", method));
	
	method.set_name("acos");
	method.set_input({ (var)"var" });
	method.set_syntax({ "acos", "(", "var", ")" });
	method.set_functiondef({ "acos", "(", "var", ")" });
	method.set_relative();
	basemethods.insert(std::pair<std::string, Method >("acos", method));
	
	method.set_name("asin");
	method.set_input({ (var)"var" });
	method.set_syntax({ "asin", "(", "var", ")" });
	method.set_functiondef({ "asin", "(", "var", ")" });
	method.set_relative();
	basemethods.insert(std::pair<std::string, Method >("asin", method));
	
	method.set_name("atan");
	method.set_input({ (var)"var" });
	method.set_syntax({ "atan", "(", "var", ")" });
	method.set_functiondef({ "atan", "(", "var", ")" });
	method.set_relative();
	basemethods.insert(std::pair<std::string, Method >("atan", method));
	
	method.set_name("root");
	method.set_input({ "base", "var" });
	method.set_syntax({ "root", "base" "(", "var", ")" });
	method.set_functiondef({ "root", "base", "(", "var", ")" });
	method.set_relative();
	basemethods.insert(std::pair<std::string, Method >("root", method));
	
	method.set_name("ln");
	method.set_input({ (var)"var" });
	method.set_syntax({ "ln", "(", "var", ")" });
	method.set_functiondef({ "ln", "(", "var", ")" });
	method.set_relative();
	basemethods.insert(std::pair<std::string, Method >("ln", method));
	
	method.set_name("log");
	method.set_input({ "base", "var" });
	method.set_syntax({ "log", "base", "(", "var", ")" });
	method.set_functiondef({ "log", "(", "var", ")" });
	method.set_relative();
	basemethods.insert(std::pair<std::string, Method >("log", method));
	
	//mapping all member functions	TODO: add parenthesis and comma
	//basefunctions.insert(std::pair<std::string, Method(MathMethod::*)(std::vector<var>&)>("()", &MathMethod::parenthesis));
	basefunctions.insert(std::pair<std::string, var(MathMethod::*)(std::vector<var>&)>("^", &MathMethod::power));
	basefunctions.insert(std::pair<std::string, var(MathMethod::*)(std::vector<var>&)>("*", &MathMethod::multiply));
	basefunctions.insert(std::pair<std::string, var(MathMethod::*)(std::vector<var>&)>("+", &MathMethod::add));
	basefunctions.insert(std::pair<std::string, var(MathMethod::*)(std::vector<var>&)>("-", &MathMethod::subtract));
	basefunctions.insert(std::pair<std::string, var(MathMethod::*)(std::vector<var>&)>("exp", &MathMethod::exponential));
	basefunctions.insert(std::pair<std::string, var(MathMethod::*)(std::vector<var>&)>("cos", &MathMethod::cosine));
	basefunctions.insert(std::pair<std::string, var(MathMethod::*)(std::vector<var>&)>("sin", &MathMethod::sine));
	basefunctions.insert(std::pair<std::string, var(MathMethod::*)(std::vector<var>&)>("tan", &MathMethod::tangent));
	basefunctions.insert(std::pair<std::string, var(MathMethod::*)(std::vector<var>&)>("acos", &MathMethod::arccosine));
	basefunctions.insert(std::pair<std::string, var(MathMethod::*)(std::vector<var>&)>("asin", &MathMethod::arcsine));
	basefunctions.insert(std::pair<std::string, var(MathMethod::*)(std::vector<var>&)>("atan", &MathMethod::arctangent));
	basefunctions.insert(std::pair<std::string, var(MathMethod::*)(std::vector<var>&)>("root", &MathMethod::root));
	basefunctions.insert(std::pair<std::string, var(MathMethod::*)(std::vector<var>&)>("ln", &MathMethod::natural_logarithm));
	basefunctions.insert(std::pair<std::string, var(MathMethod::*)(std::vector<var>&)>("log", &MathMethod::logarithm));
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
	else
	{
		//print too many input error message
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
	else
	{
		//print too many input error message
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
	else
	{
		//print too many input error message
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
	else
	{
		//print too many input error message
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
	else
	{
		//print too many input error message
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
	else
	{
		//print too many input error message
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
	else
	{
		//print too many input error message
	}
	return ans;
}

var MathMethod::arccosine(std::vector<var>& inputs)
{
	var ans("ans");

	if (inputs.size() == 2)
	{
		if (inputs[1].unknown == true)
		{
			ans.value = acos(inputs[1].value);
			ans.unknown = true;
		}
	}
	else
	{
		//print too many input error message
	}
	return ans;
}

var MathMethod::arcsine(std::vector<var>& inputs)
{
	var ans("ans");

	if (inputs.size() == 2)
	{
		if (inputs[1].unknown == true)
		{
			ans.value = acos(inputs[1].value);
			ans.unknown = true;
		}
	}
	else
	{
		//print too many input error message
	}
	return ans;
}

var MathMethod::arctangent(std::vector<var>& inputs)
{
	var ans("ans");

	if (inputs.size() == 2)
	{
		if (inputs[1].unknown == true)
		{
			ans.value = atan(inputs[1].value);
			ans.unknown = true;
		}
	}
	else
	{
		//print too many input error message
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
			ans.value = pow(inputs[1].value, 1 / inputs[0].value);
			ans.unknown = true;
		}
	}
	else
	{
		//print too many input error message
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
	else
	{
		//print too many input error message
	}
	return ans;
}

var MathMethod::logarithm(std::vector<var>& inputs)
{
	var ans("ans");

	if (inputs.size() == 1)	//default 10
	{
		if (inputs[0].unknown == true)
		{
			ans.value = log(inputs[0].value) / log(10);
			ans.unknown = true;
		}
	}
	else if (inputs.size() == 2)
	{
		if ((inputs[0].unknown == true) && (inputs[1].unknown == true))
		{
			ans.value = log(inputs[1].value) / log(inputs[0].value);
			ans.unknown = true;
		}
	}
	else
	{
		//print too many input error message
	}
	return ans;
}

std::map<std::string, Method>* MathMethod::return_Method()
{
	return &(this->basemethods);
}

var MathMethod::functions(std::string functionname)
{
	return (this->*(basefunctions[functionname]))(input);
}