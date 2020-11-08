#pragma once
#include <cstdio>
#include "IMovable.h"
#include <GLFW/glfw3.h> 

class Component : public IMovable {

protected:
	Component *parent;
	bool is_selected = false;
public:
	virtual ~Component() {};
	void setParent(Component *component)
	{
		parent = component;
	}

	Component *getParent()const { return parent; }

	virtual void add(Component *component) {}
	virtual void remove(Component*component) {}
	virtual bool isComposite() { // we can distinguish Composite(true) from Leaf(false)
		return false;
	}

	void move(float delta, MoveDirection moveDirection, glm::vec3 lookPositon = glm::vec3(0))override {};

	bool isSelected() { return is_selected; }
	virtual void setSelected(bool selected) { is_selected = selected; }

	virtual void operation()	   = 0;
	virtual std::size_t getCount() = 0;
	virtual GLint getID()		   = 0;
};