#pragma once

#include <vector>
#include "util.h"
#include <cstdio>

#include "Component.h"
#include "Shader.h"

#define GL_POSITION_LAYOUT 0
#define GL_COLOR_LAYOUT 1
#define SHADER_SELECT_LOCATION "is_selected"

//Component:Leaf

class Mesh : public Component 
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
		Shader *m_shader;

		static GLint idGenerator;
		GLint m_ID;

	public:
		//constructors,desctructors
		Mesh(std::vector<util::Vertex>, std::size_t,Shader *shader);
		~Mesh() {}

		//openGL
		void bind();
		void unbind();

		//Component
		void operation() override;
		inline std::size_t getCount() override { return m_numberOfVert; }
		inline bool isComposite() override { return false; }
		inline void move(float delta, MoveDirection moveDirection, glm::vec3 lookPositon = glm::vec3(0))override {}
		inline GLint getID()override { return m_ID; }
		inline void newScale() override { return; }

		//getters, setters
		inline std::size_t getNumberOfVert() { return this->m_numberOfVert; }
		inline void setShader(Shader *shader) { this->m_shader = shader; }

		//other
		void updateModel(glm::mat4&);
};

