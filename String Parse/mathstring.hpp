#pragma once

#include <cmath>
#include <complex>
#include <string>
#include <vector>

#include "stringprocess.hpp"
#include "functiondeveloper.hpp"

class MathString : public CommandString
{
protected:
	std::vector<std::vector<std::size_t>> locations;	//locations of parsed operators in parsed string
	std::vector<std::string> queue;	//order commands

public:
	MathString();
	~MathString() {}

	void setlocations();
	//void PEMDAS();	

	//base functions
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
	this->parse_at("!");
	this->parse_at("=");
	this->parse_at("<");
	this->parse_at(">");
	this->parse_at("==");
	this->parse_at("<=");
	this->parse_at(">=");
	//this->parse_at("&&");
	//this->parse_at("||");
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
		locations.push_back(foundat);
	}
	//sort locations? check if it's necesessary
}
/*
void MathString::PEMDAS()
{

}
*/