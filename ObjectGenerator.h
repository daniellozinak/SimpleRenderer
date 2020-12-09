#pragma once
#include <vector>
#include "Shader.h"
#include "Object.h"


class ObjectGenerator
{
	private:
		static ObjectGenerator m_instance;
		ObjectGenerator();

		glm::vec3 m_randomScale();
		float m_randomRotation();
		float m_randomFloat();

		const char* m_meshPath = "./Objects/lowpoly_tree.obj";
		const glm::vec3 m_rotationAxis = glm::vec3(0, 1, 0);
		const float m_maxScale = 1.5f;
		const float m_minScale = 0.4f;

	public:
		ObjectGenerator(const ObjectGenerator&) = delete;
		static ObjectGenerator& getInstance();

		Object* getRandomObject(glm::vec3 position,Shader *shader);
};

