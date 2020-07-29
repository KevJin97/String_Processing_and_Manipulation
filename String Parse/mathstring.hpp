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
	Subroutine function;

	void define_method(std::string& functionname);
	void changetype();

public:
	MathString();

	void getinput();
};

void MathString::define_method(std::string& functionname)
{
	if (!this->function.isoperator(functionname))
	{
		Method method;
		method.name = functionname;
		
		CommandString in;
		in.parse_at(this->string_isolate);

		std::cout << "Write syntax: ";
		in.getinput();
		method.syntax = in.return_parsed();

		std::cout << "Define the function: ";
		in.getinput();
		method.functiondef = in.return_parsed();

		for (std::size_t i = 0; i < method.syntax.size(); i++)
		{
			if (method.syntax[i].compare(functionname) != 0)
			{
				for (std::size_t j = 0; j < this->string_isolate.size(); j++)
				{
					if (method.syntax[i].compare(this->string_isolate[j]) != 0)
					{
						if (method.input.size() == 0)
						{
							method.input.push_back(new var(method.syntax[i]));
						}
						else
						{
							bool exists = false;
							for (std::size_t k = 0; k < method.input.size(); k++)
							{
								if (method.input[k]->varname.compare(method.syntax[i]) == 0)
								{
									exists = true;
									break;
								}
							}
							if (exists)
							{
								method.input.push_back(new var(method.syntax[i]));
							}
						}
					}
				}
			}
		}
		method.setrelative();
		function.define(method);
	}
	else
	{
		std::cout << "There is already a function named \"" << functionname << "\"" << std::endl;	//may implement overloading later
	}
}

MathString::MathString()
{
	this->function = Subroutine(new MathFunctions);
}

void MathString::getinput()
{
	std::string input;

	std::getline(std::cin, input);

	this->parsed = this->parse(input);

	if (this->string_isolate.size())
	{
		for (std::size_t index = 0; index < this->string_isolate.size(); index++)
		{
			this->isolate(this->string_isolate[index]);
		}
	}

	//specific operations. will be removed if voice control ever gets working
	this->changetype();
	if (this->parsed[0].compare("run") == 0)
	{
		this->function.run(this->sublist(1));
	}
	else if (this->parsed[0].compare("define") == 0)
	{
		if (this->parsed.size() > 1)
		{
			this->define_method(this->parsed[1]);
		}
		else
		{
			std::cout << "Enter name of function: ";
			std::cin >> input;
			this->define_method(input);
		}
	}

}

void MathString::changetype()
{
	for (std::size_t i = 0; i < this->parsed.size(); i++)
	{
		if ((this->parsed.front().compare("i") == 0) || (this->parsed.back().compare("i") == 0))
		{
			//change from mathfunctions to complexfunctions
			break;
		}
	}
}