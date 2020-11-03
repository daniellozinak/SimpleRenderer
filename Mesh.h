#pragma once

#include <vector>
#include "util.h"
#include <cstdio>


#define GL_POSITION_LAYOUT 0
#define GL_COLOR_LAYOUT 1


class Mesh
{
	private:
		void m_initVert(std::vector<util::Vertex>, std::size_t);
		void m_init();
		std::vector<glm::vec3> m_pos;
		std::vector<glm::vec3> m_col;
		std::size_t m_numberOfVert;

		GLuint m_VBOPos;
		GLuint m_VBOCol;
		GLuint m_VAO;
	public:
		Mesh(std::vector<util::Vertex>, std::size_t);

		void bind();

		inline std::size_t getNumberOfVert() { return this->m_numberOfVert; }
};

