#pragma once

class LEDCheckSource
{
public:
	LEDCheckSource();
	~LEDCheckSource();

	bool Valid();
	void LoadFromFile(const char* file);
	void SaveToFile(const char* file);
protected:
	void SetValid(bool valid);
private:
	bool m_valid;
};