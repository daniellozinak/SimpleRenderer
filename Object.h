#pragma once
#include <GL/glew.h>
#include <cstdio>
#include <vector>
#include "util.h"
#include "Shader.h"

#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp>



#define GL_POSITION_LAYOUT 0
#define GL_COLOR_LAYOUT 1


class Object
{
public:
	Object();
	Object(std::vector<util::Vertex>, std::size_t);
	Object(std::vector<util::Vertex>, std::size_t, glm::mat4);

	GLuint getVAO();
	std::size_t getCount();

	glm::mat4 getModelMatrix();

	void rotate();

	void draw();

	void move(glm::vec3);

	void setShader(Shader*);

	~Object();

private:
	std::vector<glm::vec3> m_pos;
	std::vector<glm::vec3> m_col;
	std::size_t m_numberOfVert;

	GLuint m_VBOPos;
	GLuint m_VBOCol;
	GLuint m_VAO;

	glm::mat4 m_modelMatrix;

	void m_initVert(std::vector<util::Vertex>, std::size_t);
	void m_init();

	Shader *m_shader;

};