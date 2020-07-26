#pragma once

#include "Var.hpp"
#include "MethodTypes.hpp"

//TODO: consider: '>', '<', '>=', '<=', '==', '!='
class MathFunctions : public Functions
{
private:
	std::map<std::string, void(MathFunctions::*)(std::vector<std::string>&, var&)> functions;
	
protected:
	//Pretty self-explanatory
	//Method parenthesis(std::vector<std::string> parsed, std::size_t open, std::size_t close);
	void equate(std::vector<std::string>& command, var& output) {}
	void parenthesis(std::vector<std::string>& inputs, var& output) {}
	void power(std::vector<std::string>& inputs, var& output) {}
	void multiply(std::vector<std::string>& inputs, var& output) {}
	void divide(std::vector<std::string>& inputs, var& output) {}
	void add(std::vector<std::string>& inputs, var& output) {}
	void subtract(std::vector<std::string>& inputs, var& output) {}
	void exponential(std::vector<std::string>& inputs, var& output) {}
	void cosine(std::vector<std::string>& inputs, var& output) {}
	void sine(std::vector<std::string>& inputs, var& output) {}
	void tangent(std::vector<std::string>& inputs, var& output) {}
	void arccosine(std::vector<std::string>& inputs, var& output) {}
	void arcsine(std::vector<std::string>& inputs, var& output) {}
	void arctangent(std::vector<std::string>& inputs, var& output) {}
	void root(std::vector<std::string>& inputs, var& output) {}
	void natural_logarithm(std::vector<std::string>& inputs, var& output) {}
	void logarithm(std::vector<std::string>& inputs, var& output) {}

public:
	MathFunctions();

	inline void function(std::vector<std::string>& command, std::size_t& operatorlocation, std::vector<var>& variables, var& output) {}
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
	this->functions.insert(std::pair<std::string, void(MathFunctions::*)(std::vector<std::string>&, var&)>("=", &MathFunctions::equate));
	this->functions.insert(std::pair<std::string, void(MathFunctions::*)(std::vector<std::string>&, var&)>("^", &MathFunctions::power));
	this->functions.insert(std::pair<std::string, void(MathFunctions::*)(std::vector<std::string>&, var&)>("*", &MathFunctions::multiply));
	this->functions.insert(std::pair<std::string, void(MathFunctions::*)(std::vector<std::string>&, var&)>("/", &MathFunctions::divide));
	this->functions.insert(std::pair<std::string, void(MathFunctions::*)(std::vector<std::string>&, var&)>("+", &MathFunctions::add));
	this->functions.insert(std::pair<std::string, void(MathFunctions::*)(std::vector<std::string>&, var&)>("-", &MathFunctions::subtract));
	this->functions.insert(std::pair<std::string, void(MathFunctions::*)(std::vector<std::string>&, var&)>("exp", &MathFunctions::exponential));
	this->functions.insert(std::pair<std::string, void(MathFunctions::*)(std::vector<std::string>&, var&)>("cos", &MathFunctions::cosine));
	this->functions.insert(std::pair<std::string, void(MathFunctions::*)(std::vector<std::string>&, var&)>("sin", &MathFunctions::sine));
	this->functions.insert(std::pair<std::string, void(MathFunctions::*)(std::vector<std::string>&, var&)>("tan", &MathFunctions::tangent));
	this->functions.insert(std::pair<std::string, void(MathFunctions::*)(std::vector<std::string>&, var&)>("acos", &MathFunctions::arccosine));
	this->functions.insert(std::pair<std::string, void(MathFunctions::*)(std::vector<std::string>&, var&)>("asin", &MathFunctions::arcsine));
	this->functions.insert(std::pair<std::string, void(MathFunctions::*)(std::vector<std::string>&, var&)>("atan", &MathFunctions::arctangent));
	this->functions.insert(std::pair<std::string, void(MathFunctions::*)(std::vector<std::string>&, var&)>("root", &MathFunctions::root));
	this->functions.insert(std::pair<std::string, void(MathFunctions::*)(std::vector<std::string>&, var&)>("ln", &MathFunctions::natural_logarithm));
	this->functions.insert(std::pair<std::string, void(MathFunctions::*)(std::vector<std::string>&, var&)>("log10", &MathFunctions::logarithm));

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
/*
void MathFunctions::equate(std::vector<std::string>& inputs, var& output)
{
	if (inputs.size() == 2)
	{
		if (!inputs[0].unknown && !inputs[1].unknown)
		{
			inputs[0] = inputs[1];
		}
	}
	else
	{
		//too many inputs
	}
}

void MathFunctions::parenthesis(std::vector<std::string>& inputs, var& output)
{

}

void MathFunctions::power(std::vector<std::string>& inputs, var& output)
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

void MathFunctions::multiply(std::vector<std::string>& inputs, var& output)
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

void MathFunctions::divide(std::vector<std::string>& inputs, var& output)
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

void MathFunctions::add(std::vector<std::string>& inputs, var& output)
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

void MathFunctions::subtract(std::vector<std::string>& inputs, var& output)
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

void MathFunctions::exponential(std::vector<std::string>& inputs, var& output)
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

void MathFunctions::cosine(std::vector<std::string>& inputs, var& output)
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

void MathFunctions::sine(std::vector<std::string>& inputs, var& output)
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

void MathFunctions::tangent(std::vector<std::string>& inputs, var& output)
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

void MathFunctions::arccosine(std::vector<std::string>& inputs, var& output)
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

void MathFunctions::arcsine(std::vector<std::string>& inputs, var& output)
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

void MathFunctions::arctangent(std::vector<std::string>& inputs, var& output)
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

void MathFunctions::root(std::vector<std::string>& inputs, var& output)
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

void MathFunctions::natural_logarithm(std::vector<std::string>& inputs, var& output)
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

void MathFunctions::logarithm(std::vector<std::string>& inputs, var& output)
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

void MathFunctions::function(std::vector<std::string>& command, std::size_t& operatorlocation, std::vector<var>& inputs, var& output)
{
	(this->*(functions[command[operatorlocation]]))(inputs, output);
}
*/