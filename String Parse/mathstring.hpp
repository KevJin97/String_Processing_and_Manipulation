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
	std::vector<var> varlist;	//list of variables
	//list of operators is in string_isolated
	std::vector<std::vector<std::size_t>> locations;	//all locations of the operator, index matches with string_isolated
	std::vector<std::vector<std::size_t>> queue;	//what order to do the operations, maybe switch to type: subroutine
	
	virtual void PEMDAS();	//order the queue
	void instances();	//find all operator instances in input

public:
	MathString();	//creates parse_at commands for all operators
	~MathString();
	void getinput();
};

void MathString::PEMDAS()
{
	//find index of each operator in string_isolate (same index as locations)
	//parenthesis_pairing() naturally ogranizes in order to solve

	std::size_t parenthesis[2] = { this->locate(this->string_isolate, "(")[0], this->locate(this->string_isolate, ")")[0] };
	std::vector<size_t*> openclose = parenthesis_pairing(this->locations[parenthesis[0]], this->locations[parenthesis[1]]);	//parenthesis must be paired

	/*
	std::size_t exponential = this->locate(this->string_isolate, "^")[0];

	std::size_t multiply = this->locate(this->string_isolate, "*")[0];

	std::size_t division = this->locate(this->string_isolate, "/")[0];
	
	std::size_t add = this->locate(this->string_isolate, "+")[0];

	std::size_t subtract = this->locate(this->string_isolate, "-")[0];
	*/

	//start with numbers, implement variables later
}

void MathString::instances()
{
	for (std::size_t i = 0; i < this->string_isolate.size(); i++)
	{
		this->locations.push_back(this->locate(string_isolate[i]));
	}
}

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

MathString::~MathString()
{

}

void MathString::getinput()
{

}

#endif