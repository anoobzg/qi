#pragma once
#include "ledalgrithminterface.h"

class LEDChecker : public ILEDChecker
{
public:
	LEDChecker();
	~LEDChecker();

	bool LoadFromFile(const char* file);
};