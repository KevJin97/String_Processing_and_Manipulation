#ifndef MATHSTRING_HPP
#define MATHSTRING_HPP

#include "stringprocess.hpp"
#include "functiondeveloper.hpp"
#include <cmath>
#include <complex>
#include <string>
#include <vector>

#define PI 3.14159265

//complex number class/struct

//phasor sub-class?

class MathString : public CommandString
{
protected:
	std::vector<var> varlist;	//list of variables

	std::vector<std::string> mathoperator;	//list of operators
	std::vector<std::vector<std::size_t>> locations;	//all locations of the operator

	std::vector<std::vector<std::string>> queue;	//what order to do the operations
	
	virtual void PEMDAS();	//order the queue
	void instances();	//find all operator instances

public:
	MathString();	//creates parse_at commands for all operators
	~MathString();

};

void MathString::PEMDAS()
{
	//P

	//E

	//M

	//D

	//A

	//S
}

void MathString::instances()
{

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

#endif