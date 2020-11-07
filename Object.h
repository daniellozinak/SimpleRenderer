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


#define GL_POSITION_LAYOUT 0
#define GL_COLOR_LAYOUT 1


//Component:Composite

class Object : public Component
{
	private:
		glm::mat4 m_modelMatrix;
		glm::vec3 m_position;
		std::size_t m_count = 0;

		//object moze mat viac Meshes (kompozit)
		std::list<Component*> m_children;
	public:
		//constructors,destructors
		Object();
		Object(glm::mat4);
		~Object() {}

		//IMovable
		void move(float delta, MoveDirection moveDirection, glm::vec3 lookPositon) override;

		//Composite
		void add(Component *component)override;
		void remove(Component*component)override;
		void operation() override;
		inline std::size_t getCount() override { return 0; } //Object it self has getCount() = 0, only meshes have getCount()>0
		inline bool isComposite()override { return true; }

		//getters,setters
		inline glm::mat4 getModelMatrix() { return this->m_modelMatrix; }
		void setPosition(glm::vec3);
		inline bool isSelected() { return is_selected; }
		inline void changeSelected() { is_selected = !is_selected; }
};