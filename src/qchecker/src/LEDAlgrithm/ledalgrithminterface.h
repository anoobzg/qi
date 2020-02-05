#pragma once

#ifdef LED_ALGRITHM_EXPORT
#define LED_ALGRITHM_API extern "C" __declspec(dllexport)
#else
#define LED_ALGRITHM_API __declspec(dllimport)
#endif

class ILEDChecker
{
public:
	virtual ~ILEDChecker() {}
	virtual bool LoadFromFile(const char* file) = 0;
};

LED_ALGRITHM_API ILEDChecker* CreateLEDChecker();
LED_ALGRITHM_API void ReleaseLEDChecker(ILEDChecker* checker);

