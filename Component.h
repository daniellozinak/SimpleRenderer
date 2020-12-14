#pragma once
#include <cstdio>
#include <GLFW/glfw3.h> 
#include "IMovable.h"



class Component : public IMovable {
	
protected:
	Component *parent;
	bool is_selected = false; //move
	float scale; //move
public:
	virtual ~Component() {};
	void setParent(Component *component)
	{
		parent = component;
	}

	Component *getParent()const { return parent; }
	inline float getScale() { return scale; } //move

	virtual void add(Component *component) {}
	virtual void remove(Component*component) {}
	virtual bool isComposite() { // we can distinguish Composite(true) from Leaf(false)
		return false;
	}

	void move(float delta, MoveDirection moveDirection, glm::vec3 lookPositon = glm::vec3(0), glm::vec3 upVector = glm::vec3(0), glm::vec3 parentMovement = glm::vec3(0))override {}; //move

	bool isSelected() { return is_selected; }//move
	virtual void setSelected(bool selected) { is_selected = selected; }//move
	inline void setScale(float scale) { this->scale = scale; }//move

	
	virtual void update()	   = 0;
	virtual std::size_t getCount() = 0;//move
	virtual GLint getID()		   = 0;//move
	virtual void newScale()		   = 0;//move
};