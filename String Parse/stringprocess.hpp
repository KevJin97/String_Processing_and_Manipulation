#ifndef STRINGPROCESS_HPP
#define STRINGPROCESS_HPP

#include <string>
#include <vector>
#include <iostream>

class CommandString
{
protected:
	std::vector<std::string> parsed;	//sorted string
	std::vector<std::string> string_ignore;	//list of strings to ignore when sorting
	std::vector<std::string> string_isolate;	//strings to continuously isolate
	
	std::vector<std::string> parse(std::string string2parse);	//separate string between each instance of whitespace
	bool checkignored(std::string check);	//check if string is on ignore list
	bool checkisolated(std::string check);	//check if string is on isolate list

public:
	CommandString();
	CommandString(std::string string2parse);	//add string2parse into parsed
	~CommandString();

	void ignore(std::string snub);	//ignore inputted string when creating parsed list
	void filter(std::string remove);	//remove all instances of the character sequence in strings
	std::vector<std::string> return_parsed();	//return parsed list
	std::vector<std::string> ignored();	//return list of ignored strings
	std::size_t size();	//return size of parsed list
	void replace(std::string carray, std::string replacement);	//replace any instance of inputted string with replacement in parsed list
	void isolate(std::string isolatestring);	//parse inputted string into its own array space
	void getinput();	//duh (and then sorts into parsed form)
	void remove(std::string string2remove);	//remove a string from parsed
	void push_back(std::string string2add);	//push_back string after parsing
	void remove_ignored(std::string removefromignored);	//remove a given string from ignored list
	void parse_at(std::string isolating);	//isolate inputted string when parsing
	std::vector<std::size_t> locate(std::string find);	//locate instances of specfic string in parsed
	std::vector<std::size_t> locate(std::vector<std::string> beingsearched, std::string searchfor);	//locate string in the inputted array
	std::vector<std::string> sublist(std::vector<std::size_t> indices);	//creates a list of indices inputted
	std::vector<std::string> sublist(std::size_t start, std::size_t end);	//creates list from indices start to end. Reverse if start > end. end maxed at size()
	std::vector<std::string> sublist(std::size_t start);	//creates a list from start to end
	std::string back2string();	//output string with whitespaces
	std::string back2string(std::vector<std::string> list);	//output list with whitespaces
	void merge(std::size_t begin, std::size_t end);	//combine the elements begin through end into one arrayspace;
	void push_to(std::string newelement, std::size_t index);	//at position of index, add the new string element

	void operator=(std::string string2parse);	//inputted string sorted based off parameters and placed in parsed
	void operator=(CommandString input);	//set CommandStrings equal to each other
	void operator=(std::vector<std::string> parsedstring);	//input parsed strings
	std::string operator[](std::size_t index);		//return index of parsed
	void operator+(std::string newstring);	//parse a new string and add it to the list
	void operator+(CommandString othercommandstring);	//merge both data bases
};

std::vector<std::string> CommandString::parse(std::string string2parse)
{
	std::vector<std::string> returnstring;
	std::size_t placehold = 0;
	std::size_t index;
	
	do //make sure algorithm doesn't start on a whitespace
	{
		index = placehold + 1;	//indexing starts at space one higher than the placehold
		
		if (string2parse[placehold] == ' ')	//continute to skip array spaces until a space is reached that doesn't have a whitespace
		{
			placehold++;
		}
		else
		{
			while (string2parse[index] != ' ' && index < string2parse.size())
			{
				index++;
			}

			char* p_hold = new char[index - placehold + 1];	//size + NULL

			for (std::size_t i = 0; i < index - placehold; i++)	//copy string2parse segment into p_hold
			{
				p_hold[i] = string2parse[placehold + i];
			}
			p_hold[index - placehold] = NULL;

			if (!this->checkignored(p_hold))	//check if string is on ignored list
			{
				returnstring.push_back(p_hold);	//push_back into return vector
			}
			delete[] p_hold;

			placehold = index + 1;	//set new placeholder at one higher than previous index
		}
	} while (index < string2parse.size());

	if (this->string_isolate.size())
	{
		for (std::size_t index = 0; index < this->string_isolate.size(); index++)
		{
			this->isolate(this->string_isolate[index]);
		}
	}

	return returnstring;
}

bool CommandString::checkignored(std::string check)
{
	bool existsonlist = false;
	std::size_t index = 0;
	
	if (index == string_ignore.size())
	{
		return existsonlist;
	}
	else
	{
		while (index < check.size())
		{
			std::size_t ignoredindex = 0;

			while (this->string_ignore[index][ignoredindex] == check[ignoredindex])
			{
				if (this->string_ignore[index].compare(check) == 0)
				{
					existsonlist = true;
				}
			}
			index++;
		}

		return existsonlist;
	}
}

bool CommandString::checkisolated(std::string check)
{
	bool existsonlist = false;
	std::size_t index = 0;

	if (index == string_isolate.size())
	{
		return existsonlist;
	}
	else
	{
		while (index < check.size())
		{
			std::size_t ignoredindex = 0;

			while (this->string_isolate[index][ignoredindex] == check[ignoredindex])
			{
				if (this->string_isolate[index].compare(check) == 0)
				{
					existsonlist = true;
				}
			}
			index++;
		}

		return existsonlist;
	}
}

CommandString::CommandString()
{

}

CommandString::CommandString(std::string string2parse)
{
	this->parsed = this->parse(string2parse);
}

CommandString::~CommandString()
{

}

void CommandString::ignore(std::string snub)	//possibly implement parsing
{
	if (!this->checkignored(snub) && this->parsed.size())
	{
		this->string_ignore.push_back(snub);
		this->remove(snub);
	}
	else
	{
		//say it already exists on the ignored list
	}
}

void CommandString::filter(std::string remove)
{
	std::vector<std::string> newparsed;
	char* p_hold;

	for (std::size_t index = 0; index < this->parsed.size(); index++)
	{
		if (this->parsed[index].size() >= remove.size())	//if the size of the string is smaller than the sequence that's being searched, go to next one
		{
			std::size_t start = 0;
			p_hold = new char[this->parsed[index].size() + 1];
			for (std::size_t i = 0; i <= this->parsed[index].size(); i++)	//null everything
			{
				p_hold[i] = NULL;
			}
			std::size_t holdindex = 0;

			while (remove.size() <= this->parsed[index].size() - start)	//check the min num times
			{
				std::size_t location = this->parsed[index].find(remove, start);

				if (location == std::string::npos)	//wasn't found
				{
					for (; start < this->parsed[index].size(); start++, holdindex++)
					{
						p_hold[holdindex] = this->parsed[index][start];
					}
					break;
				}
				else	//copy up to remove
				{
					for (; start < location; start++, holdindex++)
					{
						p_hold[holdindex] = this->parsed[index][start];
					}
				}
				start = location + remove.size();	//start = location of remove + length of remove
			}

			if (p_hold[0] != NULL)	//make sure it's not empty
			{
				newparsed.push_back(p_hold);
			}
			delete[] p_hold;
		}
		else
		{
			newparsed.push_back(this->parsed[index]);
		}
	}

	this->parsed.clear();
	this->parsed = newparsed;
	
	if (this->parsed.size())
	{
		//warning
	}
}

std::vector<std::string> CommandString::return_parsed()
{
	return this->parsed;
}

std::vector<std::string> CommandString::ignored()	//add error
{
	if (this->string_ignore.size())
	{
		return string_ignore;
	}
	else
	{
		std::vector<std::string> vec = { "NA" };
		return vec;
	}
}

std::size_t CommandString::size()
{
	return parsed.size();
}

void CommandString::replace(std::string carray, std::string replacement)
{
	if (!this->checkignored(replacement) && this->parsed.size())
	{
		std::vector<std::size_t> instances;
		for (std::size_t index = 0; index < this->parsed.size(); index++)
		{
			if (this->parsed[index].compare(carray) == 0)
			{
				this->parsed[index] = replacement;
			}
		}
	}
	else
	{
		//warning
	}
}

void CommandString::isolate(std::string isolatestring)	//MAYBE USE SUBSTR?
{
	std::vector<std::string> newparsed;
	char* p_hold;

	for (std::size_t index = 0; index < this->parsed.size(); index++)
	{
		if (this->parsed[index].size() >= isolatestring.size())	//if the size of the string is smaller than the sequence that's being searched, go to next one
		{
			std::size_t start = 0;

			while (isolatestring.size() <= this->parsed[index].size() - start)	//check the min num times
			{
				std::size_t location = this->parsed[index].find(isolatestring, start);

				if (location == std::string::npos)	//wasn't found
				{
					p_hold = new char[this->parsed[index].size() - start + 1];
					p_hold[this->parsed[index].size() - start] = NULL;
					for (std::size_t count = 0; start < this->parsed[index].size(); count++, start++)
					{
						p_hold[count] = this->parsed[index][start];
					}

					newparsed.push_back(p_hold);
					delete[] p_hold;
					break;
				}
				else if (location == start)	//if location of string is same as indexing starting point
				{
					p_hold = new char[isolatestring.size() + 1];
					for (std::size_t i = 0; i < isolatestring.size(); i++)
					{
						p_hold[i] = isolatestring[i];
					}
					p_hold[isolatestring.size()] = NULL;

					newparsed.push_back(p_hold);

					delete[] p_hold;
				}
				else	//copy previous string and isolatedstring
				{
					p_hold = new char[location - start + 1];
					p_hold[location - start] = NULL;
					for (std::size_t count = 0; start < location; count++, start++)
					{
						p_hold[count] = this->parsed[index][start];
					}

					newparsed.push_back(p_hold);
					delete[] p_hold;
					
					p_hold = new char[isolatestring.size() + 1];
					for (std::size_t i = 0; i < isolatestring.size(); i++)
					{
						p_hold[i] = isolatestring[i];
					}
					p_hold[isolatestring.size()] = NULL;

					newparsed.push_back(p_hold);

					delete[] p_hold;
				}
				start = location + isolatestring.size();	//start = location of isolatestring + length of isolatestring
			}
		}
		else
		{
			newparsed.push_back(this->parsed[index]);
		}
	}

	this->parsed.clear();
	this->parsed = newparsed;
}

void CommandString::getinput()
{
	std::string input;

	std::getline(std::cin, input);

	this->parsed = this->parse(input);
}

void CommandString::remove(std::string string2remove)
{
	if (this->parsed.size())
	{
		std::vector<std::string> newparsed;

		for (std::size_t index = 0; index < this->parsed.size(); index++)
		{
			if (this->parsed[index].compare(string2remove) != 0)
			{
				newparsed.push_back(this->parsed[index]);
			}
		}
		this->parsed.clear();
		this->parsed = newparsed;
	}
}

void CommandString::push_back(std::string string2add)
{
	if (!this->checkignored(string2add))
	{
		this->parsed.push_back(string2add);
	}
	else
	{
		//error saying string2add has been blacklisted
	}
}

void CommandString::remove_ignored(std::string removefromignored)	//maybe implement parsing later
{
	if (this->string_ignore.size())
	{
		std::vector<std::string> newignoredlist;

			std::size_t index = 0;
			while (index < this->string_ignore.size() && this->string_ignore[index].compare(removefromignored) != 0)
			{
				newignoredlist.push_back(this->string_ignore[index]);
					index++;
			}
		this->string_ignore.clear();
			this->string_ignore = newignoredlist;
	}
	else
	{
		//error
	}
}

void CommandString::parse_at(std::string isolating)	//possibly implement parsing?
{
	if (!this->checkisolated(isolating))
	{
		this->string_isolate.push_back(isolating);
		this->isolate(isolating);
	}
	else
	{
		//warning
	}
}

std::vector<std::size_t> CommandString::locate(std::string find)
{
	std::vector<std::size_t> locations;

	if (this->parsed.size())
	{
		for (std::size_t index = 0; index < this->parsed.size(); index++)
		{
			if (this->parsed[index].compare(find) == 0)
			{
				locations.push_back(index);
			}
		}
	}
	else
	{
		//error
	}
	return locations;
}

std::vector<std::size_t> CommandString::locate(std::vector<std::string> beingsearched, std::string searchfor)
{
	std::vector<std::size_t> locations;
	for (std::size_t index = 0; index < beingsearched.size(); index++)
	{
		if (beingsearched[index].compare(searchfor) == 0)
		{
			locations.push_back(index);
		}
	}
	return locations;
}

std::vector<std::string> CommandString::sublist(std::vector<std::size_t> indices)
{
	std::vector<std::string> substringlist;

	if (this->parsed.size())
	{
		for (std::size_t i = 0; i < indices.size() && indices[i] < this->parsed.size(); i++)
		{
			substringlist.push_back(this->parsed[indices[i]]);
		}

		if (substringlist.size() == 0)
		{
			//no strings located at those locations
		}
	}
	else
	{
		//error, string doesn't exist
	}
	return substringlist;
}

std::vector<std::string> CommandString::sublist(std::size_t start, std::size_t end)
{
	std::vector<std::string> substringlist;

	if (this->parsed.size())
	{
		if (end >= this->parsed.size())
		{
			end = this->parsed.size() - 1;
		}
		
		if (start < end)
		{
			for (; start <= end; start++)
			{
				substringlist.push_back(this->parsed[start]);
			}	
		}
		else if (end > start)
		{
			for (; end >= start; end--)
			{
				substringlist.push_back(this->parsed[end]);
			}
		}
		else
		{
			substringlist.push_back(this->parsed[start]);	//start == end
		}
	}
	else
	{
		//error
	}
	
	return substringlist;
}

std::vector<std::string> CommandString::sublist(std::size_t start)
{
	std::vector<std::string> substringlist;
	
	if (this->parsed.size())
	{
		for (; start < this->parsed.size(); start++)
		{
			substringlist.push_back(this->parsed[start]);
		}
	}
	else
	{
		//error
	}

	return substringlist;
}

std::string CommandString::back2string()
{
	std::string converted;
	
	if (this->size())
	{
		//total character space = sum of all string.size() + size	includes NULL
		std::size_t charspace = 0;
		for (std::size_t i = 0; i < this->parsed.size(); i++)
		{
			charspace += this->parsed[i].size();
		}
		charspace += this->size();

		char* string = new char[charspace];
		string[charspace - 1] = NULL;
		charspace = 0;

		for (std::size_t i = 0; i < this->parsed[0].size(); i++)	//copy first arrayspace
		{
			string[charspace] = this->parsed[0][i];
			charspace++;
		}
		for (std::size_t index = 1; index < this->size(); index++)	//add a space then copy the arrayspace
		{
			string[charspace] = ' ';
			charspace++;
			for (std::size_t i = 0; i < this->parsed[index].size(); i++)
			{
				string[charspace] = this->parsed[index][i];
				charspace++;
			}
		}

		converted = string;
		delete[] string;
	}
	else
	{
		//error
	}
	return converted;
}

std::string CommandString::back2string(std::vector<std::string> list)
{
	std::string converted;

	if (this->size())
	{
		//total character space = sum of all string.size() + list.size()	includes NULL
		std::size_t charspace = 0;
		for (std::size_t i = 0; i < list.size(); i++)
		{
			charspace += list[i].size();
		}
		charspace += list.size();

		char* string = new char[charspace];
		string[charspace - 1] = NULL;
		charspace = 0;

		for (std::size_t i = 0; i < list[0].size(); i++)	//copy first arrayspace
		{
			string[charspace] = list[0][i];
			charspace++;
		}
		for (std::size_t index = 1; index < list.size(); index++)	//add a space then copy the arrayspace
		{
			string[charspace] = ' ';
			charspace++;
			for (std::size_t i = 0; i < list[index].size(); i++)
			{
				string[charspace] = list[index][i];
				charspace++;
			}
		}

		converted = string;
		delete[] string;
	}
	else
	{
		//error
	}

	return converted;
}

void CommandString::merge(std::size_t begin, std::size_t end)
{
	if (begin < end)
	{
		if (end >= this->parsed.size())	//ensure it doesn't go over the bounds
		{
			end = this->parsed.size() - 1;
		}

		std::vector<std::string> list;

		for (std::size_t index = 0; index < begin; index++)
		{
			list.push_back(this->parsed[index]);
		}
		
		std::string mergedstring;
		mergedstring = this->parsed[begin];

		for (begin++; begin <= end; begin++)
		{
			mergedstring += this->parsed[begin];
		}

		list.push_back(mergedstring);

		for (end++; end < this->parsed.size(); end++)
		{
			list.push_back(this->parsed[end]);
		}

		this->parsed.clear();
		this->parsed = list;
	}
	else
	{
		//error
	}
}

void CommandString::push_to(std::string newelement, std::size_t index)
{
	if (index >= this->size())
	{
		this->parsed.push_back(newelement);
	}
	else
	{
		std::vector<std::string> hold;
		
		for (std::size_t i = 0; i < index; i++)
		{
			hold.push_back(this->parsed[i]);
		}
		hold.push_back(newelement);
		for (; index < this->size(); index++)
		{
			hold.push_back(this->parsed[index]);
		}
		this->parsed.clear();
		this->parsed = hold;
	}
}

void CommandString::operator=(std::string string2parse)
{
	if (this->parsed.size() != 0)
	{
		this->parsed.clear();
	}
	this->parsed = this->parse(string2parse);
	
}

void CommandString::operator=(CommandString input)
{
	this->parsed.clear();

	for (std::size_t i = 0; i < input.size(); i++)
	{
		this->parsed.push_back(input[i]);
	}
	this->string_ignore = input.ignored();
}

void CommandString::operator=(std::vector<std::string> parsedstring)
{
	this->parsed = parsedstring;

	if (this->string_ignore.size())	//ignore any matching strings
	{
		for (std::size_t index = 0; index < this->string_ignore.size(); index++)
		{
			this->ignore(this->string_ignore[index]);
		}
	}
	if (this->string_isolate.size())	//isolate any matching strings
	{
		for (std::size_t index = 0; index < this->string_isolate.size(); index++)
		{
			this->isolate(this->string_isolate[index]);
		}
	}
}

std::string CommandString::operator[](std::size_t index)	//work on error
{
	if (this->parsed.size())
	{
		return this->parsed[index];
	}
	else
	{
		return "0";
	}
}

void CommandString::operator+(std::string newstring)
{
	std::vector<std::string> newvector = this->parse(newstring);
	for (std::size_t index = 0; index < newvector.size(); index++)
	{
		this->parsed.push_back(newvector[index]);
	}
}

void CommandString::operator+(CommandString othercommandstring)
{
	for (std::size_t index = 0; index < othercommandstring.size(); index++)
	{
		this->parsed.push_back(othercommandstring[index]);
	}
	std::vector<std::string> newisolated = othercommandstring.ignored();
	for (std::size_t index = 0; index < newisolated.size(); index++)
	{
		if (!this->checkignored(newisolated[index]))
		{
			this->string_ignore.push_back(newisolated[index]);
		}
	}
}

#endif