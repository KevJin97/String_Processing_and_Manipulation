#ifndef MATHSTRING_HPP
#define MATHSTRING_HPP

#include "stringprocess.hpp"
#include "functiondeveloper.hpp"
#include <cmath>
#include <complex>
#include <string>
#include <vector>

class MathString : public CommandString
{
protected:
	std::vector<std::vector<std::size_t>> location;

public:
	MathString();
	~MathString() {}

	void setlocations();

	//test code
	void test()
	{
		setlocations();
		
		for (std::size_t i = 0; i < location.size(); i++)
		{
			for (std::size_t j = 0; j < location[i].size(); j++)
			std::cout << location[i][j] << std::endl;
		}
	}
};

MathString::MathString()
{
	this->parse_at(",");

	//operators
	this->parse_at("(");
	this->parse_at(")");
	this->parse_at("+");
	this->parse_at("-");
	this->parse_at("*");
	this->parse_at("/");
	this->parse_at("^");
	this->parse_at("=");
	this->parse_at("<");
	this->parse_at(">");
	this->parse_at("<=");
	this->parse_at(">=");
	this->parse_at("[");
	this->parse_at("]");

	//functions
	this->parse_at("exp");
	this->parse_at("cos");
	this->parse_at("sin");
	this->parse_at("tan");
	this->parse_at("acos");
	this->parse_at("asin");
	this->parse_at("atan");
	this->parse_at("sqrt");
	this->parse_at("log");
	this->parse_at("ln");
}

void MathString::setlocations()
{
	std::vector<std::size_t> foundat;

	for (std::size_t isolateindex = 0; isolateindex < this->string_isolate.size(); isolateindex++)
	{
		foundat = this->locate(string_isolate[isolateindex]);
		location.push_back(foundat);
	}
}

#endif