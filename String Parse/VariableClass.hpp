#pragma once

#include <string>
#include <vector>

//possibly template this
struct var
{
	std::string varname;
	double value;
	std::string type;
	bool unknown;

	var();
	var(std::string data);
	var(double value);

	bool isnumber(std::string& data);

	void operator=(var input);
	void operator=(std::string data);
};

var::var()
{
	this->value = 0;
	this->unknown = true;
}

var::var(std::string data)
{
	if (!this->isnumber(data))
	{
		this->varname = data;
		this->value = 0;	//unusuable if unknown false
		this->type = "double";
		this->unknown = false;
	}
	else
	{
		this->value = std::stod(data);
		this->type = "double";
		this->unknown = true;
	}
}

var::var(double value)
{
	this->varname = "num";
	this->value = value;
	this->type = "double";
	this->unknown = true;
}

bool var::isnumber(std::string& data)
{
	if (data.size() > 0)
	{
		for (std::size_t i = 0; i < data.size(); i++)
		{
			if (('0' > data[i]) || (data[i] > '9'))
			{
				return false;
			}
			else
			{
				break;
			}
		}
		return true;
	}
	else
	{
		return false;
	}
}

void var::operator=(var input)
{
	this->varname = input.varname;
	this->value = input.value;
	this->type = input.type;
	this->unknown = input.unknown;
}

void var::operator=(std::string data)
{
	if (!this->isnumber(data))
	{
		this->varname = data;
		this->value = 0;	//unusuable if unknown false
		this->type = "double";
		this->unknown = false;
	}
	else
	{
		this->value = std::stod(data);
		this->type = "double";
		this->unknown = true;
	}
}