#include "CallbackData.h"

CallbackData CallbackData::m_instance;

CallbackData &CallbackData::getInstance()
{
	return m_instance;
}

CallbackData::CallbackData(){}