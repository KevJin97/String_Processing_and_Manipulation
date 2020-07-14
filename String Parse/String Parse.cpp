#include <iostream>
#include <string>
#include "stringprocess.hpp"
#include "mathstring.hpp"
#include "functiondeveloper.hpp"

int main()
{
	CommandString inputmanage;
	Subroutine test;

	for (;;)
	{
		inputmanage.getinput();

		if (inputmanage[0].compare("define") == 0)
		{
			test.define(inputmanage[1]);
			test.test();
		}
		else
		{
			test.solve();
		}
	}
	
	/*
	for (;;)
	{
		//TODO: remove parenthesis from all syntax. Parenthesis will be added to main Methods
		//TODO: add a queuing process
		//TODO: if any input is a Method with no output, add to bottom of queue... may cause infinite loop. Fix thatasa

		std::vector<std::string> method_syntax = { "number1", "||", "number2" };	//replaces the syntax list
		std::vector<std::string> method_definition = { "(", "1", "/", "number1", "+", "1", "/", "number2", ")", "^", "-", "1" };	//replaces functiondef
		std::string paralleloperator = "||";		//operator name in Method


		//components of struct var
		std::vector<std::string> variable_names = { "number1", "number2" };	//replaces the variable input list
		std::vector<std::string> variable_values;	//replaces variable value list
		

		std::cout << "Input: ";	//user input
		inputmanage.getinput();
		

		//algorithm to set to turn Method values into something useful
		std::vector<std::size_t> multiplylocation = inputmanage.locate(paralleloperator);	//locates instances in user input
		if (multiplylocation.size() != 0)
		{
			std::vector<std::size_t> location_in_method_syntax = inputmanage.locate(method_syntax, paralleloperator);	//locate the operator in the syntax: for basefunctions may hard code?
			//probably induce recursion as part of the method process
			//add location of variables into Method
			//queue would be like CommandString except as a list of Method(maybe?) so that solve() can directly access variable outputs for every operation
				//recursion would apply when a Method contains parenthesis. () would contain everything between them and then stored as its own Method in the main queue
				//queue should have Methods set in the order of parsed_string and another part that has a list of indexes to know what to run first
			//function for solve: functionname(size_t, size_t). Allows for direct variable input in inputted equations
			
			//set up variable locations for storage
			std::vector<std::vector<std::size_t>> variable_locations_in_syntax;	//stores variable locations
			for (std::size_t i = 0; i < variable_names.size(); i++)	
			{
				variable_locations_in_syntax.push_back(inputmanage.locate(method_syntax, variable_names[i]));
			}
			std::vector<std::vector<int>> relative_from_operator_location;
			for (std::size_t i = 0; i < variable_locations_in_syntax.size(); i++)
			{
				for (std::size_t j = 0; j < variable_locations_in_syntax[i].size(); j++)
				{
					std::vector<int> tempvec;
					tempvec.push_back(variable_locations_in_syntax[i][j] - multiplylocation[0]);
					relative_from_operator_location.push_back(tempvec);
				}
			}

			//Turning Method instructions into an actual process
				//Needed: relative_from_operator_location variable locations and operator locations from the syntax
			

			//check output
			std::cout << "Multiply(" << variable_values[0] << ", " << variable_values[1] << ")" << std::endl;
		}
	}
	*/

	return 0;
}
