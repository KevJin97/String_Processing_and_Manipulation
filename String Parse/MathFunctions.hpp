#pragma once

#include "Var.hpp"
#include "MethodTypes.hpp"

//TODO: consider: '>', '<', '>=', '<=', '==', '!='
struct MathFunctions : public Functions
{
	std::map<std::string, void(MathFunctions::*)(std::vector<std::string>&)> basefunctions;
	
	//Method parenthesis(std::vector<std::string> parsed, std::size_t open, std::size_t close);
	void equate(std::vector<std::string>& inputs);
	void parenthesis(std::vector<std::string>& inputs);
	void power(std::vector<std::string>& inputs);
	void multiply(std::vector<std::string>& inputs);
	void divide(std::vector<std::string>& inputs);
	void add(std::vector<std::string>& inputs);
	void subtract(std::vector<std::string>& inputs);
	void exponential(std::vector<std::string>& inputs);
	void cosine(std::vector<std::string>& inputs);
	void sine(std::vector<std::string>& inputs);
	void tangent(std::vector<std::string>& inputs);
	void arccosine(std::vector<std::string>& inputs);
	void arcsine(std::vector<std::string>& inputs);
	void arctangent(std::vector<std::string>& inputs);
	void root(std::vector<std::string>& inputs);
	void natural_logarithm(std::vector<std::string>& inputs);
	void logarithm(std::vector<std::string>& inputs);

public:
	MathFunctions();
};

MathFunctions::MathFunctions()
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
		"-",
		"="
	};
	
	//mapping all member functions	TODO: add parenthesis and comma
	//basefunctions.insert(std::pair<std::string, Method(MathMethod::*)(std::vector<var>&)>("()", &MathMethod::parenthesis));
	basefunctions.insert(std::pair<std::string, void(MathFunctions::*)(std::vector<var>&)>("=", &MathFunctions::equate));
	basefunctions.insert(std::pair<std::string, void(MathFunctions::*)(std::vector<var>&)>("^", &MathFunctions::power));
	basefunctions.insert(std::pair<std::string, void(MathFunctions::*)(std::vector<var>&)>("*", &MathFunctions::multiply));
	basefunctions.insert(std::pair<std::string, void(MathFunctions::*)(std::vector<var>&)>("+", &MathFunctions::add));
	basefunctions.insert(std::pair<std::string, void(MathFunctions::*)(std::vector<var>&)>("-", &MathFunctions::subtract));
	basefunctions.insert(std::pair<std::string, void(MathFunctions::*)(std::vector<var>&)>("exp", &MathFunctions::exponential));
	basefunctions.insert(std::pair<std::string, void(MathFunctions::*)(std::vector<var>&)>("cos", &MathFunctions::cosine));
	basefunctions.insert(std::pair<std::string, void(MathFunctions::*)(std::vector<var>&)>("sin", &MathFunctions::sine));
	basefunctions.insert(std::pair<std::string, void(MathFunctions::*)(std::vector<var>&)>("tan", &MathFunctions::tangent));
	basefunctions.insert(std::pair<std::string, void(MathFunctions::*)(std::vector<var>&)>("acos", &MathFunctions::arccosine));
	basefunctions.insert(std::pair<std::string, void(MathFunctions::*)(std::vector<var>&)>("^", &MathFunctions::power)); 
	basefunctions.insert(std::pair<std::string, void(MathFunctions::*)(std::vector<var>&)>("asin", &MathFunctions::arcsine));
	basefunctions.insert(std::pair<std::string, void(MathFunctions::*)(std::vector<var>&)>("atan", &MathFunctions::arctangent));
	basefunctions.insert(std::pair<std::string, void(MathFunctions::*)(std::vector<var>&)>("root", &MathFunctions::root));
	basefunctions.insert(std::pair<std::string, void(MathFunctions::*)(std::vector<var>&)>("ln", &MathFunctions::natural_logarithm));
	basefunctions.insert(std::pair<std::string, void(MathFunctions::*)(std::vector<var>&)>("log", &MathFunctions::logarithm));
}

void MathFunctions::equate(std::vector<std::string>& inputs)
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

void MathFunctions::parenthesis(std::vector<std::string>& inputs)
{

}

void MathFunctions::power(std::vector<std::string>& inputs)
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

void MathFunctions::multiply(std::vector<std::string>& inputs)
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

void MathFunctions::divide(std::vector<std::string>& inputs)
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

void MathFunctions::add(std::vector<std::string>& inputs)
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

void MathFunctions::subtract(std::vector<std::string>& inputs)
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

void MathFunctions::exponential(std::vector<std::string>& inputs)
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

void MathFunctions::cosine(std::vector<std::string>& inputs)
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

void MathFunctions::sine(std::vector<std::string>& inputs)
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

void MathFunctions::tangent(std::vector<std::string>& inputs)
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

void MathFunctions::arccosine(std::vector<std::string>& inputs)
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

void MathFunctions::arcsine(std::vector<std::string>& inputs)
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

void MathFunctions::arctangent(std::vector<std::string>& inputs)
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

void MathFunctions::root(std::vector<std::string>& inputs)
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

void MathFunctions::natural_logarithm(std::vector<std::string>& inputs)
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

void MathFunctions::logarithm(std::vector<std::string>& inputs)
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