#pragma once

#include <string>
#include <vector>
#include <typeinfo>

#include "MethodTypes.hpp"

//variables
class var
{
private:
	bool initialized;
	
public:
	std::string varname;
	void* value;
	std::string type;
	bool unknown;

	var();
	var(std::string name);
	var(void* value, std::string type);
	var(std::size_t size, std::string type);
	var(std::string name, std::size_t size, std::string type);
	~var();

	void clear();
	void changetype(std::size_t size, std::string type);
	void set(var variable);

	void operator=(var newvar);
};

var::var()
{
	this->initialized = false;
}

var::var(std::string name)
{
	this->varname = name;
	this->unknown = true;

	this->initialized = false;
}

var::var(void* value, std::string type)
{
	this->value = value;
	this->type = type;
	this->unknown = false;

	this->initialized = true;
}

var::var(std::size_t size, std::string type)
{
	this->value = malloc(size);
	this->type = type;
	this->unknown = true;

	this->initialized = true;
}

var::var(std::string name, std::size_t size, std::string type)
{
	this->varname = name;
	this->value = malloc(size);
	this->type = type;
	this->unknown = true;

	this->initialized = true;
}

var::~var()
{
	this->clear();
}

void var::clear()
{
	if (this->initialized)
	{
		free(this->value);
		this->type.clear();
	}
	if (this->varname.size())
	{
		this->varname.clear();
	}
}

void var::changetype(std::size_t size, std::string type)
{
	if (this->initialized)
	{
		free(this->value);
	}
	this->type = type;
	this->value = malloc(size);
}

void var::set(var variable)
{
	if (this->initialized)
	{
		free(this->value);
	}
	
	if (this->type.size() == 0)
	{
		this->type = variable.type;
	}
	
	this->value = variable.value;
}

void var::operator=(var newvar)
{
	if (this->initialized)
	{
		if (this->type.compare(newvar.type) == 0)
		{
			free(this->value);
			this->value = newvar.value;
		}
		else
		{
			std::cout << "Variable types are not the same" << std::endl;
		}
	}
	else
	{
		//error: it wasn't initialized
	}
}