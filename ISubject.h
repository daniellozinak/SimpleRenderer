
#pragma once

#include "IObserver.h"
#include <list>


class ISubject {
protected:
	std::list<IObserver*> m_observers;
public:
	void attach(IObserver *observer);
	void detach(IObserver *observer);
	virtual void notify() = 0;

};