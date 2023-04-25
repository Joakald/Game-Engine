#pragma once

#include <string>
#include <iostream>

void Error(std::string message)
{
	throw std::runtime_error(message);
}