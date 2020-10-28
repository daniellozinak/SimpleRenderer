#include "ISubject.h"

void ISubject::attach(IObserver* observer)
{
	this->m_observers.emplace_back(observer);
}

void ISubject::detach(IObserver* observer)
{
	this->m_observers.remove(observer);
}