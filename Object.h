#pragma once
#include <GL/glew.h>
#include <cstdio>
#include <vector>
#include "util.h"
#include "IMovable.h"
#include "Mesh.h"

#include "Component.h"

#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp>


//Component:Composite


class Object : public Component
{
	private:
		glm::mat4 m_modelMatrix;
		glm::vec3 m_position;
		std::size_t m_count = 0;

		std::list<Component*> m_children;
		void newScale() override;
		void m_move(glm::vec3);

		glm::vec3 m_scale = glm::vec3(1);
	public:
		//constructors,destructors
		Object();
		Object(glm::mat4);
		~Object() {}

		//IMovable
		void move(float delta, MoveDirection moveDirection, glm::vec3 lookPositon = glm::vec3(0),glm::vec3 upVector = glm::vec3(0),glm::vec3 parentMovement = glm::vec3(0)) override;

		//Composite
		void add(Component *component)override;
		void remove(Component*component)override;
		void operation() override;
		inline std::size_t getCount() override { return 0; } //Object it self has getCount() = 0, only meshes have getCount()>0
		inline bool isComposite()override { return true; }
		inline GLint getID()override { return -1; }
		void setSelected(bool selected) override;

		//getters,setters
		inline glm::mat4 getModelMatrix() { return this->m_modelMatrix; }
		inline void setModelMatatrix(glm::mat4 model) { this->m_modelMatrix = model; }
		inline std::list<Component*> getChildren() { return m_children; }
		void setPosition(glm::vec3);
		void setScale(glm::vec3);
		void setRotate(float degrees,glm::vec3);
};