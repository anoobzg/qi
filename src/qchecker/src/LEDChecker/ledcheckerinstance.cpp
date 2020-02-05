#include "ledcheckerinstance.h"
#include "ledalgrithminterface.h"
#include <QLibrary>

ILEDChecker* instance = nullptr;
QLibrary library("LEDAlgrithm");

void InitializeLEDCheckerInstance()
{
	if (instance == nullptr)
	{
		if (library.load())
		{
			typedef  ILEDChecker* (*CreateLEDChecker)();
			QFunctionPointer ptr = library.resolve("CreateLEDChecker");
			CreateLEDChecker pfn = reinterpret_cast<CreateLEDChecker>(ptr);
			instance = pfn();
		}
	}
}

ILEDChecker* GetLEDCheckerInstance()
{
	assert(instance);
	return instance;
}

void ReleaseLEDCheckerInstance()
{
	if (instance)
	{
		typedef void (*ReleaseLEDChecker)(ILEDChecker* checker);
		QFunctionPointer ptr = library.resolve("ReleaseLEDChecker");
		ReleaseLEDChecker pfn = reinterpret_cast<ReleaseLEDChecker>(ptr);
		pfn(instance);

		library.unload();
	}
}