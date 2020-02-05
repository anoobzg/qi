#pragma once

class ILEDChecker;
void InitializeLEDCheckerInstance();
ILEDChecker* GetLEDCheckerInstance();
void ReleaseLEDCheckerInstance();
