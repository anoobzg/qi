#include "ledchecksource.h"

LEDCheckSource::LEDCheckSource()
	:m_valid(false)
{

}

LEDCheckSource::~LEDCheckSource()
{

}

bool LEDCheckSource::Valid()
{
	return m_valid;
}

void LEDCheckSource::SetValid(bool valid)
{
	m_valid = valid;
}

void LEDCheckSource::LoadFromFile(const char* file)
{

}

void LEDCheckSource::SaveToFile(const char* file)
{

}