#include "Object.h"
#include <glm/vec3.hpp>

//GLuint Object::m_VAO;


Object::Object(Mesh* mesh)
{
	this->m_modelMatrix = glm::mat4(1.0f);
	this->setPosition(glm::vec3(0, 0, 0));
	this->m_mesh = mesh;
}

Object::Object(Mesh* mesh, glm::mat4 modelMatrix)
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



void Object::setShader(Shader*shader)
{
	this->m_shader = shader;
}

void Object::setPosition(glm::vec3 position)
{
	this->m_position = position;
	this->m_modelMatrix = glm::translate(this->m_modelMatrix, position);
}

void Object::draw()
{
	this->m_mesh->bind();
	this->m_shader->bind();
	this->m_shader->sendUniform("modelMatrix", this->m_modelMatrix);
	glDrawArrays(GL_TRIANGLES, 0,m_mesh->getNumberOfVert());
}

void Object::rotate()
{
	this->m_modelMatrix = glm::rotate(this->m_modelMatrix, 0.01f, glm::vec3(1.0f, 0.0f, 0.0f));
}

glm::mat4 Object::getModelMatrix() { return this->m_modelMatrix; }


Object::~Object()
{
}