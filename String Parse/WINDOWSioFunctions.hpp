#pragma once

#include <Windows.h>

#include "Var.hpp"
#include "MethodTypes.hpp"

class ioFunctions : public Functions
{
private:
	std::map<std::string, void(ioFunctions::*)(std::vector<var*>&, var&)> functions;

protected:
	void getcursorlocation(std::vector<var*>& inputs, var& output);
	void movecursor(std::vector<var*>& inputs, var& outputs);
	void leftclick(std::vector<var*>& inputs, var& outputs);
	void rightclick(std::vector<var*>& inputs, var& outputs);
	void type(std::vector<var*>& inputs, var& outputs);

public:
	ioFunctions();
	~ioFunctions();

	void function(std::vector<std::string>& command, std::size_t& operatorlocation, Method& method, var& output);
};

ioFunctions::ioFunctions()
{
	Method method;

	method.name = "GetCursorLocation";
	method.input = { new var("x"), new var("y") };
	method.syntax = { "GetCursorLocation", "(", "x", ",", "y", ")" };
	method.functiondef = { "GetCursorLocation", "(", "x", ",", "y", ")" };
	method.setrelative();
	this->method_list.insert(std::pair <std::string, Method>(method.name, method));

	method.clear();
	method.name = "MoveCursor";
	method.input = { new var("x"), new var("y") };
	method.syntax = { "MoveCursor", "(", "x", ",", "y", ")" };
	method.functiondef = { "MoveCursor", "(", "x", ",", "y", ")" };
	method.setrelative();
	this->method_list.insert(std::pair <std::string, Method>(method.name, method));

	method.clear();
	method.name = "LeftClick";
	method.syntax = { "LeftClick" };
	method.functiondef = { "LeftClick" };
	method.setrelative();
	this->method_list.insert(std::pair <std::string, Method>(method.name, method));

	method.clear();
	method.name = "RightClick";
	method.syntax = { "RightClick" };
	method.functiondef = { "RightClick" };
	method.setrelative();
	this->method_list.insert(std::pair <std::string, Method>(method.name, method));

	method.clear();
	method.name = "Type";
	method.input = { new var("string") };
	method.syntax = { "Type", "(", "string", ")" };
	method.functiondef = { "Type", "(", "string", ")" };
	method.setrelative();
	this->method_list.insert(std::pair <std::string, Method>(method.name, method));

	this->functions.insert(std::pair<std::string, void(ioFunctions::*)(std::vector<var*>&, var&)>("GetCursorLocation", &ioFunctions::getcursorlocation));
	this->functions.insert(std::pair<std::string, void(ioFunctions::*)(std::vector<var*>&, var&)>("MoveCursor", &ioFunctions::movecursor));
	this->functions.insert(std::pair<std::string, void(ioFunctions::*)(std::vector<var*>&, var&)>("LeftClick", &ioFunctions::leftclick));
	this->functions.insert(std::pair<std::string, void(ioFunctions::*)(std::vector<var*>&, var&)>("RightClick", &ioFunctions::rightclick));
	this->functions.insert(std::pair<std::string, void(ioFunctions::*)(std::vector<var*>&, var&)>("Type", &ioFunctions::type));
}

ioFunctions::~ioFunctions()
{
	for (std::map<std::string, Method>::iterator i = this->method_list.begin(); i != this->method_list.end(); i++)
	{
		this->method_list[i->first].clear();
	}
}

void ioFunctions::getcursorlocation(std::vector<var*>& inputs, var& output)
{
	if ((inputs[0]->unknown == false) && (inputs[1]->unknown == false))
	{
		POINT p;
		GetCursorPos(&p);
		*inputs[0] = p.x;
		*inputs[1] = p.y;
	}
	else
	{

	}
}

void ioFunctions::movecursor(std::vector<var*>& inputs, var& outputs)
{
	if ((inputs[0]->unknown == false) && (inputs[1]->unknown == false))
	{
		SetCursorPos(inputs[0]->value, inputs[1]->value);
	}
	else
	{

	}
}

void ioFunctions::leftclick(std::vector<var*>& inputs, var& outputs)
{
	if (inputs.size() == 0)
	{
		INPUT Input = { 0 };
		
		Input.type = INPUT_MOUSE;
		Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
		::SendInput(1, &Input, sizeof(INPUT));
		//::ZeroMemory(&Input, sizeof(INPUT));
		
		//Input.type = INPUT_MOUSE;
		Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
		Input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
		::SendInput(1, &Input, sizeof(INPUT));
		//::ZeroMemory(&Input, sizeof(INPUT));
	}
	else
	{
		std::cout << "Something went hella wrong cause this really should not happen" << std::endl;
	}
}

void ioFunctions::rightclick(std::vector<var*>& inputs, var& outputs)
{
	if (inputs.size() == 0)
	{
		INPUT Input = { 0 };
		
		Input.type = INPUT_MOUSE;
		Input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
		::SendInput(1, &Input, sizeof(INPUT));
		//::ZeroMemory(&Input, sizeof(INPUT));
		
		//Input.type = INPUT_MOUSE;
		Input.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
		::SendInput(1, &Input, sizeof(INPUT));
		//::ZeroMemory(&Input, sizeof(INPUT));
	}
	else
	{
		std::cout << "Something went hella wrong cause this really should not happen" << std::endl;
	}
}

void ioFunctions::type(std::vector<var*>& inputs, var& outputs)
{
	std::string totype = "testing";	//replace this later
	INPUT Input;
	Input.type = INPUT_KEYBOARD;
	Input.ki.wScan = 0;
	Input.ki.time = 0;
	Input.ki.dwExtraInfo = 0;
	Input.ki.dwFlags = 0;

	enum alphabet { a = 0x41, b, c, d, e, f, g, h, i, j, k, l,
					m, n, o, p, q, r, s, t, u, v, w, x, y, z };

	for (std::size_t index = 0; index < totype.size(); index++)
	{
		switch (totype[index])
		{
		case 'a':
			Input.ki.wVk = a;
			break;

		case 'b':
			Input.ki.wVk = b;
			break;

		case 'c':
			Input.ki.wVk = c;
			break;

		case 'd':
			Input.ki.wVk = d;
			break;

		case 'e':
			Input.ki.wVk = e;
			break;

		case 'f':
			Input.ki.wVk = f;
			break;

		case 'g':
			Input.ki.wVk = g;
			break;

		case 'h':
			Input.ki.wVk = h;
			break;

		case 'i':
			Input.ki.wVk = i;
			break;

		case 'j':
			Input.ki.wVk = j;
			break;

		case 'k':
			Input.ki.wVk = k;
			break;

		case 'l':
			Input.ki.wVk = l;
			break;

		case 'm':
			Input.ki.wVk = m;
			break;

		case 'n':
			Input.ki.wVk = n;
			break;

		case 'o':
			Input.ki.wVk = o;
			break;

		case 'p':
			Input.ki.wVk = p;
			break;

		case 'q':
			Input.ki.wVk = q;
			break;

		case 'r':
			Input.ki.wVk = r;
			break;

		case 's':
			Input.ki.wVk = s;
			break;

		case 't':
			Input.ki.wVk = t;
			break;

		case 'u':
			Input.ki.wVk = u;
			break;

		case 'v':
			Input.ki.wVk = v;
			break;

		case 'w':
			Input.ki.wVk = w;
			break;

		case 'x':
			Input.ki.wVk = x;
			break;

		case 'y':
			Input.ki.wVk = y;
			break;

		case 'z':
			Input.ki.wVk = z;
			break;
		}

		SendInput(1, &Input, sizeof(INPUT));
		Input.ki.dwFlags = KEYEVENTF_KEYUP;
		SendInput(1, &Input, sizeof(INPUT));
	}
}

void ioFunctions::function(std::vector<std::string>& command, std::size_t& operatorlocation, Method& method, var& output)
{
	(this->*(functions[command[operatorlocation]]))(method.input, output);
}