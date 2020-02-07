#pragma once

#ifdef LED_ALGRITHM_EXPORT
#define LED_ALGRITHM_API extern "C" __declspec(dllexport)
#else
#define LED_ALGRITHM_API __declspec(dllimport)
#endif

struct OrderCloudFlags
{
	unsigned char* flags;
};

struct OrderCloud
{
	int row;
	int column;
	float* position;
	unsigned char* color;
	OrderCloudFlags flags;
};

class ILEDChecker
{
public:
	virtual ~ILEDChecker() {}
	virtual bool LoadFromFile(const char* file) = 0;
	virtual void SaveToFile(const char* file) = 0;

	virtual bool GetRawCloud(OrderCloud& cloud) = 0;
};

LED_ALGRITHM_API ILEDChecker* CreateLEDChecker();
LED_ALGRITHM_API void ReleaseLEDChecker(ILEDChecker* checker);

