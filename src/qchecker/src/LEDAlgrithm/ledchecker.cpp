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
	//std::cout << "LoadFromFile" << std::endl;
	m_source.LoadFromFile(file);
	return m_source.Valid();
}

void LEDChecker::SaveToFile(const char* file)
{
	//std::cout << "SaveToFile" << std::endl;
	m_source.SaveToFile(file);
}

bool LEDChecker::GetRawCloud(OrderCloud& cloud)
{
	if (m_source.Valid())
	{
		return true;
	}
	return false; 
}

ILEDChecker* CreateLEDChecker()
{
	return new LEDChecker();
}

void ReleaseLEDChecker(ILEDChecker* checker)
{
	if (checker) delete checker;
}