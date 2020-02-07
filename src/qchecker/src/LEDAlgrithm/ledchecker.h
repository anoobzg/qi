#pragma once
#include "ledalgrithminterface.h"
#include "ledchecksource.h"

class LEDChecker : public ILEDChecker
{
public:
	LEDChecker();
	~LEDChecker();

	bool LoadFromFile(const char* file);
	void SaveToFile(const char* file);

	bool GetRawCloud(OrderCloud& cloud);

private:
	LEDCheckSource m_source;
};