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

void Object::move(float delta, MoveDirection moveDirection,glm::vec3 lookDirection, glm::vec3 upVector)
{
	if (!isSelected()) {return; }
	glm::vec3 newPosition = this->m_position;
	glm::vec3 moveVector = glm::cross(lookDirection, upVector);
	switch (moveDirection)
	{
	case MoveDirection::FORWARDS:
		newPosition += lookDirection *(i_speed * delta);
		break;
	case MoveDirection::BACKWARDS:
		newPosition -= lookDirection * (i_speed * delta);
		break;
	case MoveDirection::LEFT:
		newPosition -= moveVector * (i_speed * delta);
		break;
	case MoveDirection::RIGHT:
		newPosition += moveVector * (i_speed * delta);
		break;
	case MoveDirection::UP:
		newPosition += upVector * (i_speed * delta);
		break;
	case MoveDirection::DOWN:
		newPosition -= upVector * (i_speed * delta);
		break;
	}

	this->setPosition(this->m_position - newPosition);
	for (Component * component : m_children)
	{
		component->move(delta, moveDirection, lookDirection);
	}
}


void Object::setPosition(glm::vec3 moveVector) 
{
	this->m_position += moveVector;
	this->m_modelMatrix = glm::translate(this->m_modelMatrix, moveVector);
	this->operation();
}

void Object::setSelected(bool selected)
{
	is_selected = selected;

	for (Component *component : m_children)
	{
		if(selected)
			component->setSelected(selected);
	}
	
}

void Object::newScale()
{
	this->m_modelMatrix = glm::scale(this->m_modelMatrix, glm::vec3(scale));
}

void Object::add(Component *component)
{
	this->m_children.emplace_back(component);
	component->setParent(this);

	//set root scale
	if (this->parent == nullptr && this->isComposite())
	{
		this->scale = 1;
	}

	//set the scale to parent scale /2
	else if (this->parent != nullptr && this->isComposite())
	{
		component->setScale(this->getScale() / 2);
		component->newScale();
	}

	if (!component->isComposite()) //check if component is not composite, otherwise we would add Component 2x into ComponentManager 
	{
		componentManager.addObject(this);
		componentManager.addObject(component);
	}
	/* 
		"this" needs to be added first, otherwise n-th mesh will be drawn on (n-1)th position
		because of the way Render class loops trough Components
	*/
}

void Object::remove(Component *component)
{
	for (Component * tmp_component : this->m_children)
	{
		if (tmp_component->isComposite()) // if object is made of another objects
		{
			Object *obj = reinterpret_cast<Object*>(tmp_component);
			for (Component *cmp : obj->getChildren()) // iterate over all meshes and delete them
			{
				obj->remove(cmp);
			}
			componentManager.removeObject(obj); 
			componentManager.removeObject(this);
		}
	}

	this->m_children.remove(component);
	component->setParent(nullptr);
	componentManager.removeObject(component);
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

void Object::setScale(glm::vec3 scale)
{
	this->m_modelMatrix = glm::scale(m_modelMatrix, scale);
}

void Object::setRotate(float degrees,glm::vec3 rotate)
{
	m_modelMatrix = glm::rotate(m_modelMatrix, degrees,rotate);
}
