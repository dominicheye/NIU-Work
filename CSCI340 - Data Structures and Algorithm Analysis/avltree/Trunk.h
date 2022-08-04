#pragma once

#include <string>

struct Trunk
{
	Trunk* prev;
	std::string str;

	Trunk(Trunk* prev, std::string str)
	{
		this->prev = prev;
		this->str = str;
	}
};