#pragma once
#include <cstdio>

class Component {

protected:
	Component *parent;
public:
	virtual ~Component() {};
	void setParent(Component *component)
	{
		parent = component;
	}

	Component *getParent()const { return parent; }

	virtual void add(Component *component) {}
	virtual void remove(Component*component) {}
	virtual bool isComposite() { //added so we can distinguish Composite(true) from Leaf(false)
		return false;
	}

	virtual void operation() = 0;
	virtual std::size_t getCount() = 0;
};