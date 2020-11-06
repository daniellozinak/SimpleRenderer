#include "Object.h"
#include <glm/vec3.hpp>
#include "ComponentManager.h"

ComponentManager &componentManager = ComponentManager::getInstance();

Object::Object()
{
	this->m_modelMatrix = glm::mat4(1.0f);
	this->setPosition(glm::vec3(0, 0, 0));
}

Object::Object(glm::mat4 modelMatrix)
{
	this->m_modelMatrix = modelMatrix;
	this->setPosition(glm::vec3(0, 0, 0));
}

void Object::move(float delta, MoveDirection moveDirection)
{
	glm::vec3 move = glm::vec3(0, 0, 0);
	switch (moveDirection)
	{
	case MoveDirection::FORWARDS:
		move.z += (i_speed * delta);
		break;
	case MoveDirection::BACKWARDS:
		move.z -= (i_speed * delta);
		break;
	case MoveDirection::LEFT:
		move.x -= (i_speed * delta);
		break;
	case MoveDirection::RIGHT:
		move.y += (i_speed * delta);
		break;
	case MoveDirection::UP:
		move.y += (i_speed * delta);
		break;
	case MoveDirection::DOWN:
		move.y -= (i_speed * delta);
		break;
	}

	this->setPosition(move);
}

//TODO 1: fix positioning
// doesnt work like it should, needs to move other components too
void Object::setPosition(glm::vec3 position) 
{
	this->m_position = position;
	this->m_modelMatrix = glm::translate(this->m_modelMatrix, position);
	this->operation();
}

void Object::add(Component *component)
{
	this->m_children.emplace_back(component);
	componentManager.addObject(this); 
	componentManager.addObject(component);
	component->setParent(this);

	/* 
		"this" needs to be added first, otherwise n-th mesh will be drawn on (n-1)th position
		because of the way Render class loops trough Components
	*/
}


void Object::remove(Component *component)
{
	this->m_children.remove(component);
	componentManager.removeObject(component);
	componentManager.removeObject(this);
	component->setParent(nullptr);
}

void Object::operation()
{
	for (Component *component : m_children)
	{
		if (!component->isComposite())
		{
			Mesh *mesh = dynamic_cast<Mesh*>(component);
			mesh->updateModel(this->m_modelMatrix);
		}
	}
}
