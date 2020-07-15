#include "Method.cpp""

//TODO: consider: '>', '<', '>=', '<=', '==', '!='
class MathMethod : public Method
{
private:
	std::map<std::string, Method> basemethods;

	//std::map<std::string, var(MathMethod::*)(std::vector<var>&)> basefunction;		//TODO Fix this implementation
	//create map for methods maybe

	//basic operators
	//Method parenthesis(std::vector<std::string> parsed, std::size_t open, std::size_t close);
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

public:
	MathMethod();	//TODO: fix

	//fix later
	var function(std::string functionname, std::vector<var>& input);	//parse through to give function result. this will be removed later for map implementation
	virtual std::vector<Method> returnmethod();	//possibly redesign this
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

	/*		TODO Reimplement this after learning how to map the function
	//mapping all member functions	TODO: add parenthesis and comma
	//basefunction.insert(std::pair<std::string, Method(MathMethod::*)(std::vector<var>&)>("()", &MathMethod::parenthesis));
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
	*/

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
			ans.value = pow(inputs[1].value, 1 / inputs[0].value);
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
	return ans;
}

std::vector<Method> MathMethod::returnmethod()		//THIS WILL BE EXCEEDINGLY INEFFICIENT but it will be used until it's fixed
{

}

var MathMethod::function(std::string functionname, std::vector<var>& input)
{
	var ans;
	ans.varname = "ans";

	if (functionname.compare("+") == 0)
	{
		ans = this->add(input);
	}
	else if (functionname.compare("-") == 0)
	{
		ans = this->subtract(input);
	}
	else if (functionname.compare("*") == 0)
	{
		ans = this->multiply(input);
	}
	else if (functionname.compare("/") == 0)
	{
		ans = this->divide(input);
	}
	else if (functionname.compare("^") == 0)
	{
		ans = this->power(input);
	}
	else if (functionname.compare("ln") == 0)
	{
		ans = this->natural_logarithm(input);
	}
	else if (functionname.compare("log") == 0)
	{
		ans = this->logarithm(input);
	}
	else if (functionname.compare("cos") == 0)
	{
		ans = this->cosine(input);
	}
	else if (functionname.compare("sin") == 0)
	{
		ans = this->sine(input);
	}
	else if (functionname.compare("tan") == 0)
	{
		ans = this->tangent(input);
	}
	else if (functionname.compare("root") == 0)
	{
		ans = this->root(input);
	}
	else if (functionname.compare("exp") == 0)
	{
		ans = this->exponential(input);
	}
	else
	{
		ans.varname = "NA";
	}
	return ans;
}