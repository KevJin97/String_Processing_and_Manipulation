#pragma once

#include <cmath>
#include <string>
#include <vector>
#include <map>
#include <utility>

#include "Var.hpp"
#include "stringprocess.hpp"
#include "MethodTypes.hpp"

std::vector<std::size_t*> parenthesis_pairing(std::vector<std::size_t> open, std::vector<std::size_t> closed)	//read order of parenthesis, make sure to erase data later. New algorithm ready
{
	std::vector<std::size_t*> paired;
	std::size_t* openclose;
	bool* used = new bool[closed.size()];

	for (std::size_t index = 0; index < closed.size(); index++)	//initialize used
	{
		used[index] = false;
	}

	if (open.size() == closed.size() && open.size() != 0)
	{
		std::size_t index = 0;
		while (index < open.size())
		{
			std::size_t sift = 0;
			openclose = new std::size_t[2];
			openclose[0] = open[open.size() - ++index];

			while (((used[sift] == true) || (open[open.size() - index] > closed[sift])) && (sift < closed.size()))
			{
				sift++;
			}

			openclose[1] = closed[sift];
			used[sift] = true;

			paired.push_back(openclose);
		}
		delete[] used;
	}
	else
	{
		//parenthesis aren't equal
	}
	return paired;
}

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

	void define(Method& method);	//defines a new function
	std::vector<var> run(std::vector<std::string> command);	//input complete command to run
	var run_method(std::vector<std::string>& command, std::size_t& operatorlocation, Method& method);	//run the function
	void erasevar(std::string& varname);	//erase the variable
	bool isvariable(std::string& input, std::vector<var*>& varlist);	//check if it's on the variable list
	bool isoperator(std::string& input);	//check if it's on operator list

	void test() {}
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
	std::vector<std::string>* p_command_mod = new std::vector<std::string>(command);
	std::vector<std::string>* p_hold = p_command_mod;
	std::vector<std::size_t> operatorlocations;
	std::vector<var> outputs;
	
	//set-up
	if (this->base->order.size() == 0)	//if there's no order, do this
	{
		for (std::size_t i = 0; i < command.size(); i++)
		{
			if (this->isoperator(command[i]))
			{
				operatorlocations.push_back(i);
			}
			else if (!this->isvariable(command[i], variables) && !var::isnumber(command[i]))
			{
				variables.push_back(new var(command[i]));
			}
		}
	}
	else
	{
		std::vector<std::size_t> baseindex;
		for (std::size_t i = 0; i < command.size(); i++)
		{
			if (this->method_list.count(command[i]) > 0)
			{
				operatorlocations.push_back(i);
			}
			else if (this->base->method_list.count(command[i]) > 0)
			{
				baseindex.push_back(i);
			}
			else if (!this->isvariable(command[i], variables) && !var::isnumber(command[i]))
			{
				variables.push_back(new var(command[i]));
			}
		}
		for (std::size_t i = 0; i < this->base->order.size(); i++)
		{
			for (std::size_t j = 0; j < baseindex.size(); j++)
			{
				if (this->base->order[i].compare(command[baseindex[j]]) == 0)
				{
					operatorlocations.push_back(baseindex[j]);
				}
			}
		}
	}

	//below may possibly be integrated with the set-up later
	outputs.resize(operatorlocations.size());

	for (std::size_t i = 0; i < operatorlocations.size(); i++)	//run methods
	{
		Method method;
		//set method
		if (this->method_list.count((*p_command_mod)[operatorlocations[i]]) > 0)
		{
			method = this->method_list[(*p_command_mod)[operatorlocations[i]]];
		}
		else if (this->base->method_list.count((*p_command_mod)[operatorlocations[i]]) > 0)
		{
			method = this->base->method_list[(*p_command_mod)[operatorlocations[i]]];
		}
		
		outputs[i] = "Out" + std::to_string(i);

		for (std::size_t varloc, j = 0; j < method.input.size(); j++)	//set inputs, program safeties later
		{
			varloc = operatorlocations[i] + method.relativelocations[j];
			
			if (this->isvariable((*p_command_mod)[varloc], variables))	//OPTIMIZE LATER
			{
				for (std::size_t k = 0; k < variables.size(); k++)
				{
					if (variables[k]->varname.compare((*p_command_mod)[varloc]) == 0)
					{
						delete method.input[j];
						method.input[j] = variables[k];
						break;
					}
				}
			}
			else if (this->isoperator((*p_command_mod)[varloc]))
			{

			}
			else if (var::isnumber((*p_command_mod)[varloc]))
			{
				*method.input[j] = (*p_command_mod)[varloc];
			}
			else    //outputs
			{
				for (std::size_t k = 0; k < outputs.size(); k++)
				{
					if (outputs[k].varname.compare((*p_command_mod)[varloc]) == 0)
					{
						*method.input[j] = outputs[k];
						break;
					}
				}
			}
		}

		outputs[i] = this->run_method(*p_command_mod, operatorlocations[i], method);	//get output
		p_hold = new std::vector<std::string>;

		for (std::size_t j = 0; j < p_command_mod->size(); j++)
		{
			if (j == operatorlocations[i] - method.operatorlocation)	//shift over locations and add the output
			{
				p_hold->push_back(outputs[i].varname);
				for (std::size_t k = i + 1; k < operatorlocations.size(); k++)	//move all remaining locations over
				{
					if (operatorlocations[k] > operatorlocations[i])
					{
						operatorlocations[k] -= method.syntax.size() - 1;
					}
				}
				j += method.syntax.size() - 1;
			}
			else
			{
				p_hold->push_back((*p_command_mod)[j]);
			}
		}
		
		delete p_command_mod;
		p_command_mod = p_hold;
		for (std::size_t i = 0; i < method.input.size(); i++)
		{
			if (!this->isvariable(method.input[i]->varname, variables))
			{
				delete method.input[i];
			}
		}
	}

	delete p_command_mod;

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

bool Subroutine::isvariable(std::string& input, std::vector<var*>& varlist)
{
	for (std::size_t i = 0; i < varlist.size(); i++)
	{
		if (varlist[i]->varname.compare(input) == 0)
		{
			return true;
		}
	}
	
	return false;
}

bool Subroutine::isoperator(std::string& input)
{
	if ((this->method_list.count(input) > 0) || (this->base->method_list.count(input) > 0))
	{
		return true;
	}
	else
	{
		return false;
	}
}