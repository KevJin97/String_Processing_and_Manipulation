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

	static bool isnumber(std::string& data);

	void operator=(var input);
	void operator=(std::string data);
};

var::var()
{
	this->varname = "NULL";
	this->value = 0;
	this->unknown = true;
}

var::var(std::string data)
{
	if (!this->isnumber(data) && (data.compare("NULL") != 0))
	{
		this->varname = data;
		this->value = 0;	//unusuable if unknown false
		this->type = "double";
		this->unknown = false;
	}
	else if (data.compare("NULL") == 0)
	{
		std::cout << "\"NULL\" cannot be used as a function name." << std::endl;
		std::cout << "Variable name has been switched to \"null\"" << std::endl;
		this->varname = "null";
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
	if (this->varname.size() == 0)
	{
		this->varname = input.varname;
	}
	this->value = input.value;
	this->type = input.type;
	this->unknown = input.unknown;
}

void var::operator=(std::string data)
{
	if (!this->isnumber(data) && (data.compare("NULL") != 0))
	{
		this->varname = data;
		this->value = 0;	//unusuable if unknown false
		this->type = "double";
		this->unknown = false;
	}
	else if (data.compare("NULL") == 0)
	{
		std::cout << "\"NULL\" cannot be used as a function name." << std::endl;
		std::cout << "Variable name has been switched to \"null\"" << std::endl;
		this->varname = "null";
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