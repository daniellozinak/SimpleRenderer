#pragma once
#include <GL/glew.h>
#include <cstdio>
#include <vector>
#include "util.h"
#include "Shader.h"
#include "IMovable.h"
#include "Mesh.h"

#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp>





#define GL_POSITION_LAYOUT 0
#define GL_COLOR_LAYOUT 1


class Object : public IMovable
{
	public:
		Object();
		Object(Mesh*);
		Object(Mesh*, glm::mat4);

		std::size_t getCount();

		glm::mat4 getModelMatrix();

		void rotate();

		void draw();

		void move(float delta, MoveDirection moveDirection) override;

		void setShader(Shader*);

		void setPosition(glm::vec3);

		~Object();

	private:
		glm::mat4 m_modelMatrix;
		glm::vec3 m_position;

		Shader *m_shader;
		Mesh *m_mesh;

};