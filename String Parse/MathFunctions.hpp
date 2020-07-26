#pragma once

#include <math.h>

#include "Var.hpp"
#include "MethodTypes.hpp"

//TODO: consider: '>', '<', '>=', '<=', '==', '!='
class MathFunctions : public Functions
{
private:
	std::map<std::string, void(MathFunctions::*)(std::vector<var>&, var&)> functions;
	
protected:
	//Pretty self-explanatory
	//Method parenthesis(std::vector<std::string> parsed, std::size_t open, std::size_t close);
	void equate(std::vector<var>& inputs, var& output);
	void parenthesis(std::vector<var>& inputs, var& output);
	void power(std::vector<var>& inputs, var& output);
	void multiply(std::vector<var>& inputs, var& output);
	void divide(std::vector<var>& inputs, var& output);
	void add(std::vector<var>& inputs, var& output);
	void subtract(std::vector<var>& inputs, var& output);
	void exponential(std::vector<var>& inputs, var& output);
	void cosine(std::vector<var>& inputs, var& output);
	void sine(std::vector<var>& inputs, var& output);
	void tangent(std::vector<var>& inputs, var& output);
	void arccosine(std::vector<var>& inputs, var& output);
	void arcsine(std::vector<var>& inputs, var& output);
	void arctangent(std::vector<var>& inputs, var& output);
	void root(std::vector<var>& inputs, var& output);
	void natural_logarithm(std::vector<var>& inputs, var& output);
	void logarithm(std::vector<var>& inputs, var& output);

public:
	MathFunctions();

	void function(std::vector<std::string>& command, std::size_t& operatorlocation, Method& method, var& output);
};

MathFunctions::MathFunctions()
{
	this->order =
	{
		"(",
		")",
		"exp",
		"cos",
		"sin",
		"tan",
		"acos",
		"asin",
		"atan",
		"root",
		"ln",
		"log10",
		"^",
		"*",
		"/",
		"+",
		"-",
		"="
	};

	//basefunctions.insert(std::pair<std::string, Method(MathMethod::*)(std::vector<var>&)>("()", &MathMethod::parenthesis));
	this->functions.insert(std::pair<std::string, void(MathFunctions::*)(std::vector<var>&, var&)>("=", &MathFunctions::equate));
	this->functions.insert(std::pair<std::string, void(MathFunctions::*)(std::vector<var>&, var&)>("^", &MathFunctions::power));
	this->functions.insert(std::pair<std::string, void(MathFunctions::*)(std::vector<var>&, var&)>("*", &MathFunctions::multiply));
	this->functions.insert(std::pair<std::string, void(MathFunctions::*)(std::vector<var>&, var&)>("/", &MathFunctions::divide));
	this->functions.insert(std::pair<std::string, void(MathFunctions::*)(std::vector<var>&, var&)>("+", &MathFunctions::add));
	this->functions.insert(std::pair<std::string, void(MathFunctions::*)(std::vector<var>&, var&)>("-", &MathFunctions::subtract));
	this->functions.insert(std::pair<std::string, void(MathFunctions::*)(std::vector<var>&, var&)>("exp", &MathFunctions::exponential));
	this->functions.insert(std::pair<std::string, void(MathFunctions::*)(std::vector<var>&, var&)>("cos", &MathFunctions::cosine));
	this->functions.insert(std::pair<std::string, void(MathFunctions::*)(std::vector<var>&, var&)>("sin", &MathFunctions::sine));
	this->functions.insert(std::pair<std::string, void(MathFunctions::*)(std::vector<var>&, var&)>("tan", &MathFunctions::tangent));
	this->functions.insert(std::pair<std::string, void(MathFunctions::*)(std::vector<var>&, var&)>("acos", &MathFunctions::arccosine));
	this->functions.insert(std::pair<std::string, void(MathFunctions::*)(std::vector<var>&, var&)>("asin", &MathFunctions::arcsine));
	this->functions.insert(std::pair<std::string, void(MathFunctions::*)(std::vector<var>&, var&)>("atan", &MathFunctions::arctangent));
	this->functions.insert(std::pair<std::string, void(MathFunctions::*)(std::vector<var>&, var&)>("root", &MathFunctions::root));
	this->functions.insert(std::pair<std::string, void(MathFunctions::*)(std::vector<var>&, var&)>("ln", &MathFunctions::natural_logarithm));
	this->functions.insert(std::pair<std::string, void(MathFunctions::*)(std::vector<var>&, var&)>("log10", &MathFunctions::logarithm));

	Method method;

	method.name = "=";
	method.input = { (var)"num1", (var)"num2" };
	method.syntax = { "num1", "=", "num2" };
	method.functiondef = { "num1", "=", "num2" };
	method.setrelative();
	this->method_list.insert(std::pair <std::string, Method>(method.name, method));

	method.clear();
	method.name = "^";
	method.input = { (var)"num1", (var)"num2" };
	method.syntax = { "num1", "^", "num2" };
	method.functiondef = { "num1", "^", "num2" };
	method.setrelative();
	this->method_list.insert(std::pair <std::string, Method>(method.name, method));

	method.clear();
	method.name = "*";
	method.input = { (var)"num1", (var)"num2" };
	method.syntax = { "num1", "*", "num2" };
	method.functiondef = { "num1", "*", "num2" };
	method.setrelative();
	this->method_list.insert(std::pair <std::string, Method>(method.name, method));

	method.clear();
	method.name = "/";
	method.input = { (var)"num1", (var)"num2" };
	method.syntax = { "num1", "/", "num2" };
	method.functiondef = { "num1", "/", "num2" };
	method.setrelative();
	this->method_list.insert(std::pair <std::string, Method>(method.name, method));

	method.clear();
	method.name = "+";
	method.input = { (var)"num1", (var)"num2" };
	method.syntax = { "num1", "+", "num2" };
	method.functiondef = { "num1", "+", "num2" };
	method.setrelative();
	this->method_list.insert(std::pair <std::string, Method>(method.name, method));

	method.clear();
	method.name = "-";
	method.input = { (var)"num1", (var)"num2" };
	method.syntax = { "num1", "-", "num2" };
	method.functiondef = { "num1", "-", "num2" };
	method.setrelative();
	this->method_list.insert(std::pair <std::string, Method>(method.name, method));

	method.clear();
	method.name = "exp";
	method.input = { (var)"num" };
	method.syntax = { "exp", "(", "num", ")" };
	method.functiondef = { "exp", "(", "num", ")" };
	method.setrelative();
	this->method_list.insert(std::pair <std::string, Method>(method.name, method));

	method.clear();
	method.name = "cos";
	method.input = { (var)"num" };
	method.syntax = { "cos", "(", "num", ")" };
	method.functiondef = { "cos", "(", "num", ")" };
	method.setrelative();
	this->method_list.insert(std::pair <std::string, Method>(method.name, method));

	method.clear();
	method.name = "sin";
	method.input = { (var)"num" };
	method.syntax = { "sin", "(", "num", ")" };
	method.functiondef = { "sin", "(", "num", ")" };
	method.setrelative();
	this->method_list.insert(std::pair <std::string, Method>(method.name, method));

	method.clear();
	method.name = "tan";
	method.input = { (var)"num" };
	method.syntax = { "tan", "(", "num", ")" };
	method.functiondef = { "tan", "(", "num", ")" };
	method.setrelative();
	this->method_list.insert(std::pair <std::string, Method>(method.name, method));

	method.clear();
	method.name = "acos";
	method.input = { (var)"num" };
	method.syntax = { "acos", "(", "num", ")" };
	method.functiondef = { "acos", "(", "num", ")" };
	method.setrelative();
	this->method_list.insert(std::pair <std::string, Method>(method.name, method));

	method.clear();
	method.name = "asin";
	method.input = { (var)"num" };
	method.syntax = { "asin", "(", "num", ")" };
	method.functiondef = { "asin", "(", "num", ")" };
	method.setrelative();
	this->method_list.insert(std::pair <std::string, Method>(method.name, method));

	method.clear();
	method.name = "atan";
	method.input = { (var)"num" };
	method.syntax = { "atan", "(", "num", ")" };
	method.functiondef = { "atan", "(", "num", ")" };
	method.setrelative();
	this->method_list.insert(std::pair <std::string, Method>(method.name, method));

	method.clear();
	method.name = "root";
	method.input = { (var)"num" };
	method.syntax = { "root", "(", "num", ")" };
	method.functiondef = { "root", "(", "num", ")" };
	method.setrelative();
	this->method_list.insert(std::pair <std::string, Method>(method.name, method));

	method.clear();
	method.name = "ln";
	method.input = { (var)"num" };
	method.syntax = { "ln", "(", "num", ")" };
	method.functiondef = { "ln", "(", "num", ")" };
	method.setrelative();
	this->method_list.insert(std::pair <std::string, Method>(method.name, method));

	method.clear();
	method.name = "log10";
	method.input = { (var)"num" };
	method.syntax = { "log10", "(", "num", ")" };
	method.functiondef = { "log10", "(", "num", ")" };
	method.setrelative();
	this->method_list.insert(std::pair <std::string, Method>(method.name, method));
}

void MathFunctions::equate(std::vector<var>& inputs, var& output)
{
	inputs[0] = inputs[1];
}

void MathFunctions::parenthesis(std::vector<var>& inputs, var& output)
{

}

void MathFunctions::power(std::vector<var>& inputs, var& output)
{
	if ((inputs[0].unknown == false) && (inputs[1].unknown == false))
	{
		output = pow(inputs[0].value, inputs[1].value);
	}
	else
	{
		//request for constraint
	}
}

void MathFunctions::multiply(std::vector<var>& inputs, var& output)
{
	if ((inputs[0].unknown == false) && (inputs[1].unknown == false))
	{
		output = inputs[0].value * inputs[1].value;
	}
	else
	{
		//request for constraint
	}
}

void MathFunctions::divide(std::vector<var>& inputs, var& output)
{
	if ((inputs[0].unknown == false) && (inputs[1].unknown == false))
	{
		output = inputs[0].value / inputs[1].value;
	}
	else
	{
		//request for constraint
	}
}

void MathFunctions::add(std::vector<var>& inputs, var& output)
{
	if ((inputs[0].unknown == false) && (inputs[1].unknown == false))
	{
		output = inputs[0].value + inputs[1].value;
	}
	else
	{
		//request for constraint
	}
}

void MathFunctions::subtract(std::vector<var>& inputs, var& output)
{
	if ((inputs[0].unknown == false) && (inputs[1].unknown == false))
	{
		output = inputs[0].value - inputs[1].value;
	}
	else if (inputs[0].unknown)
	{
		output = -inputs[1].value;
	}
	else
	{
		//request for constraint
	}
}

void MathFunctions::exponential(std::vector<var>& inputs, var& output)
{
	if (inputs[0].unknown == false)
	{
		output = exp(inputs[0].value);
	}
	else
	{
		//request for constraint
	}
}

void MathFunctions::cosine(std::vector<var>& inputs, var& output)
{
	if (inputs[0].unknown == false)
	{
		output = cos(inputs[0].value);
	}
	else
	{
		//request for constraint
	}
}

void MathFunctions::sine(std::vector<var>& inputs, var& output)
{
	if (inputs[0].unknown == false)
	{
		output = sin(inputs[0].value);
	}
	else
	{
		//request for constraint
	}
}

void MathFunctions::tangent(std::vector<var>& inputs, var& output)
{
	if (inputs[0].unknown == false)
	{
		output = tan(inputs[0].value);
	}
	else
	{
		//request for constraint
	}
}

void MathFunctions::arccosine(std::vector<var>& inputs, var& output)
{
	if (inputs[0].unknown == false)
	{
		output = acos(inputs[0].value);
	}
	else
	{
		//request for constraint
	}
}

void MathFunctions::arcsine(std::vector<var>& inputs, var& output)
{
	if (inputs[0].unknown == false)
	{
		output = asin(inputs[0].value);
	}
	else
	{
		//request for constraint
	}
}

void MathFunctions::arctangent(std::vector<var>& inputs, var& output)
{
	if (inputs[0].unknown == false)
	{
		output = atan(inputs[0].value);
	}
	else
	{
		//request for constraint
	}
}

void MathFunctions::root(std::vector<var>& inputs, var& output)
{
	if (inputs[0].unknown == false)
	{
		output = sqrt(inputs[0].value);
	}
	else
	{
		//request for constraint
	}
}

void MathFunctions::natural_logarithm(std::vector<var>& inputs, var& output)
{
	if (inputs[0].unknown == false)
	{
		output = log(inputs[0].value);
	}
	else
	{
		//request for constraint
	}
}

void MathFunctions::logarithm(std::vector<var>& inputs, var& output)
{
	if (inputs[0].unknown == false)
	{
		output = log10(inputs[0].value);
	}
	else
	{
		//request for constraint
	}
}

void MathFunctions::function(std::vector<std::string>& command, std::size_t& operatorlocation, Method& method, var& output)
{
	(this->*(functions[command[operatorlocation]]))(method.input, output);
}