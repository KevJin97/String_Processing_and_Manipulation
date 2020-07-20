#pragma once

#include <complex>	//or is it complex.h?

#include "VariableClass.hpp"
#include "MathMethod.hpp"

class ComplexMathMethod : public MathMethod
{
private:
	std::map<std::string, Method> basemethods;
	std::map<std::string, var(MathMethod::*)(std::vector<var>&)> basefunction;		//TODO Fix this implementation

protected:
	//basic operators/functions

public:
	ComplexMathMethod();
};

ComplexMathMethod::ComplexMathMethod()
{
	this->function_list =
	{

	};
}