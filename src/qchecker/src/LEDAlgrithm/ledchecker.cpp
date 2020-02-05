#include "ledchecker.h"
#include <iostream>

LEDChecker::LEDChecker()
{

}

LEDChecker::~LEDChecker()
{

}

bool LEDChecker::LoadFromFile(const char* file)
{
	std::cout << "LoadFromFIle" << std::endl;
	return true;
}

ILEDChecker* CreateLEDChecker()
{
	return new LEDChecker();
}

void ReleaseLEDChecker(ILEDChecker* checker)
{
	if (checker) delete checker;
}