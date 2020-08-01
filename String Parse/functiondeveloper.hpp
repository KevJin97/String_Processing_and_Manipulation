#pragma once

#include <cmath>
#include <string>
#include <vector>
#include <map>
#include <utility>

#include "Var.hpp"
#include "stringprocess.hpp"
#include "MethodTypes.hpp"

//TODO: create a natural language subroutine that inherits from this one
//Subroutine takes instruction sets in Method and processes it
class Subroutine
{
protected:
	Functions* base;	//holds all base functions
	std::map<std::string, Method> method_list;	//list of user-defined functions
	std::vector<var*> variable_list;	//list of variables that get defined	

	std::vector<var> execute(std::vector<std::string>& command, std::vector<var*>& variables);	//runs the inputted command and returns list of outputs

public:
	Subroutine();
	Subroutine(Functions* type);
	~Subroutine();

	std::size_t* parenthesis(std::vector<std::string>& command, std::size_t& startpoint, std::vector<var*>& variables, std::vector<var>& outputs);	//organizes when it hits a parenthesis
	void define(Method& method);	//defines a new function
	std::vector<var> run(std::vector<std::string> command);	//input complete command to run
	var run_method(std::vector<std::string>& command, std::size_t& operatorlocation, Method& method);	//run the function
	void erasevar(std::string& varname);	//erase the variable
	std::size_t isvariable(std::string& input, std::vector<var*>& varlist);	//check if it's on the variable list, returns size of varlist if not found
	bool isnumber(std::string& input);	//check if it's a number
	//TODO: create a way to check if there's a string
	bool isoperator(std::string& input);	//check if it's on operator list
};

Subroutine::Subroutine()
{
	this->base = new Functions;
}

Subroutine::Subroutine(Functions* type)
{
	this->base = type;
}

Subroutine::~Subroutine()
{
	delete this->base;

	for (std::size_t i = 0; i < this->variable_list.size(); i++)
	{
		delete this->variable_list[i];
	}

	for (std::map<std::string, Method>::iterator i = this->method_list.begin(); i != this->method_list.end(); i++)
	{
		this->method_list[i->first].clear();
	}
}

std::size_t* Subroutine::parenthesis(std::vector<std::string>& command, std::size_t& startpoint, std::vector<var*>& variables, std::vector<var>& outputs)
{
	std::size_t* startend = new std::size_t[2];
	std::size_t count = 1;
	std::size_t index = startpoint;
	startend[0] = startpoint;
	startend[1] = startpoint;

	std::vector<std::string> newcommand;

	while ((index < command.size()) || (count != 0))
	{
		if (command[index].compare("(") == 0)
		{
			count++;
		}
		else if (command[index].compare(")") == 0)
		{
			count--;
		}
		newcommand.push_back(command[index]);
		index++;
	}

	if (count == 0)		//successful
	{
		startend[1] = --index;

		var variable("OUT" + std::to_string(outputs.size()));
		variable.set(this->execute(newcommand, variables).back());

		outputs.push_back(variable);
	}
	else
	{
		std::cout << "Missing closing parenthesis" << std::endl;

		var variable("OUT" + std::to_string(outputs.size()));
		variable.changetype(sizeof(std::string), "ERROR");
		outputs.push_back(variable);
	}

	return startend;
}

void Subroutine::define(Method& method)
{
	if (!this->isoperator(method.name))
	{
		this->method_list.insert(std::pair<std::string, Method>(method.name, method));
	}
	else
	{
		std::cout << "Function \"" << method.name << "\" has already been defined" << std::endl;
	}
}

std::vector<var> Subroutine::run(std::vector<std::string> command)
{
	return this->execute(command, this->variable_list);
}

std::vector<var> Subroutine::execute(std::vector<std::string>& command, std::vector<var*>& variables)
{
	std::vector<var> outputs;
	std::vector<std::string>* p_command = new std::vector<std::string>;
	std::vector<std::size_t> operatorlocation;
	Method method;

	//set-up
	if (this->base->order.size() == 0)	//if there is no order
	{
		for (std::size_t i = 0; i < command.size(); i++)
		{
			if (command[i].compare("(") == 0)
			{
				std::size_t* locations = this->parenthesis(command, i, variables, outputs);
				
				if (locations[0] == locations[1])	//FAILURE
				{
					return outputs;
				}
				else
				{
					p_command->push_back(outputs.back().varname);
					i = locations[1];
					
					delete[] locations;
				}
			}
			else if (command[i].compare(")") == 0)	//FAILURE
			{
				std::cout << "No matching opening parenthesis" << std::endl;
				
				var variable("OUT" + std::to_string(outputs.size()));
				variable.changetype(sizeof(std::string), "ERROR");
				outputs.push_back(variable);
				
				return outputs;
			}		
			else if (this->isoperator(command[i]) || this->base->isoperator(command[i]))
			{
				p_command->push_back(command[i]);

				operatorlocation.push_back(p_command->size() - 1);
			}
			else if (!this->isnumber(command[i]) && (this->isvariable(command[i], variables) == variables.size()))
			{
				variables.push_back(new var(command[i]));
				this->base->define_var(*variables.back());
			}
			else
			{
				p_command->push_back(command[i]);
			}
		}
	}
	else
	{
		for (std::size_t i = 0; i < command.size(); i++)
		{
			if (command[i].compare("(") == 0)
			{
				std::size_t* locations = this->parenthesis(command, i, variables, outputs);

				if (locations[0] == locations[1])	//FAILURE
				{
					return outputs;
				}
				else
				{
					p_command->push_back(outputs.back().varname);
					i = locations[1];

					delete[] locations;
				}
			}
			else if (command[i].compare(")") == 0)	//FAILURE
			{
				std::cout << "No matching opening parenthesis" << std::endl;

				var variable("OUT" + std::to_string(outputs.size()));
				variable.changetype(sizeof(std::string), "ERROR");
				outputs.push_back(variable);

				return outputs;
			}
			else if (this->isoperator(command[i]))
			{
				p_command->push_back(command[i]);

				operatorlocation.push_back(p_command->size() - 1);
			}
			else if (!this->isnumber(command[i]) && (this->isvariable(command[i], variables) == variables.size()))
			{
				variables.push_back(new var(command[i]));
				this->base->define_var(*variables.back());
			}
			else
			{
				p_command->push_back(command[i]);
			}
		}
		for (std::size_t i = 0; i < p_command->size(); i++)
		{
			if (this->base->isoperator((*p_command)[i]))
			{
				operatorlocation.push_back(i);
			}
		}
	}

	for (std::size_t i = 0; i < operatorlocation.size(); i++)
	{
		//set methods
		if (this->isoperator((*p_command)[operatorlocation[i]]))
			{
				method = this->method_list[(*p_command)[operatorlocation[i]]];
			}
		else if (this->base->isoperator((*p_command)[operatorlocation[i]]))
			{
				method = this->base->method_list[(*p_command)[operatorlocation[i]]];
			}

		//set inputs
		std::vector<var> var_strings;
		for (std::size_t listloc, varlocation, j = 0; j < method.input.size(); j++)
		{
			varlocation = method.relativelocations[j] + operatorlocation[i];

			if ((listloc = this->isvariable((*p_command)[varlocation], variables)) != variables.size())
			{
				var_strings.push_back(*variables[listloc]);
			}
			else if (this->isnumber((*p_command)[varlocation]))
			{
				var variable("numstring");
				variable.changetype(sizeof(std::string), "string");
				var_strings.push_back(variable);

				std::string* temp = (std::string*)variable.value;
				*temp = (*p_command)[varlocation];
			}
			//else if (for string)
			else
			{
				//if the result is a previously outputted value
				for (std::size_t k = 0; k < outputs.size(); k++)
				{
					if ((*p_command)[varlocation].compare(outputs[k].varname) == 0)
					{
						var_strings.push_back(outputs[k]);
						break;
					}
				}
			}
		}
		std::vector<std::size_t> eraselater = this->base->set_methods(method, var_strings);	//convert inputted values into usable forms

		outputs.push_back(var("OUT" + std::to_string(outputs.size())));	//name the output
		outputs.back() = this->run_method(command, operatorlocation[i], method);	//actually run the function

		//restructure command for next iteration
		std::vector<std::string>* hold = p_command;
		p_command = new std::vector<std::string>;
		for (std::size_t j = 0; j < hold->size(); j++)
		{
			if (j == (operatorlocation[i] - method.operatorlocation))
			{
				p_command->push_back(outputs.back().varname);
				for (std::size_t k = i + 1; k < operatorlocation.size(); k++)	//move all remaining locations over
				{
					if (operatorlocation[k] > operatorlocation[i])
					{
						operatorlocation[k] -= method.syntax.size() - 1;
					}
				}
				j += method.syntax.size() - 1;
			}
			else
			{
				p_command->push_back((*hold)[j]);
			}
		}

		//deallocate
		delete hold;
		for (std::size_t i = 0; i < eraselater.size(); i++)
		{
			delete method.input[eraselater[i]];
		}
		method.clear();
	}
	
	return outputs;
}

var Subroutine::run_method(std::vector<std::string>& command, std::size_t& operatorlocation, Method& method)
{
	if (this->method_list.count(method.name) > 0)	//if it's user defined
	{
		return this->execute(method.functiondef, method.input).back();
	}
	else if (this->base->method_list.count(method.name) > 0)   //if it's a base method
	{
		var output("OUT");
		this->base->function(command, operatorlocation, method, output);
		return output;
	}
	else    //if it's neither
	{
		return this->execute(method.functiondef, method.input).back();
	}
}

void Subroutine::erasevar(std::string& varname)
{
	std::vector<var*> hold = this->variable_list;
	this->variable_list.clear();

	for (std::size_t i = 0; i < hold.size(); i++)
	{
		if (this->variable_list[i]->varname.compare(varname))
		{
			this->variable_list.push_back(hold[i]);
		}
		else if (this->variable_list[i]->varname.compare(varname) == 0)
		{
			delete variable_list[i];
			std::cout << this->variable_list[i]->varname << " has been deleted" << std::endl;
		}
	}
	if (hold.size() == this->variable_list.size())
	{
		std::cout << varname << " was not previously declared" << std::endl;
	}
}

std::size_t Subroutine::isvariable(std::string& input, std::vector<var*>& varlist)
{
	for (std::size_t i = 0; i < varlist.size(); i++)
	{
		if (varlist[i]->varname.compare(input) == 0)
		{
			return i;
		}
	}
	
	return varlist.size();
}

bool Subroutine::isnumber(std::string& input)
{
	if (input.size() > 0)
	{
		for (std::size_t i = 0; i < input.size(); i++)
		{
			if (('0' > input[i]) || (input[i] > '9') && ((input[i] != '.') || (input[i] != 'e') || (input[i] != 'E')))
			{
				return false;
			}
			return true;
		}
	}
	else
	{
		return false;
	}
}

bool Subroutine::isoperator(std::string& input)
{
	if (this->method_list.count(input) > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}