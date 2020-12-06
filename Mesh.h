#pragma once

#include <vector>
#include "util.h"
#include <cstdio>

#include "Component.h"
#include "Shader.h"

#define GL_POSITION_LAYOUT 0
#define GL_NORMAL_LAYOUT 1
#define GL_TEXTURE_LAYOUT 2
#define SHADER_SELECT_LOCATION "is_selected"

//Component:Leaf

class Mesh : public Component 
{
	private:
		void m_initVert(std::vector<util::Vertex>, std::size_t);

		GLuint m_VBOPos;
		GLuint m_VBONor;
		GLuint m_VBOTex;

		static GLint idGenerator;
		static int offset;
		GLint m_ID;

	protected:
		GLuint m_TextureID;
		Shader* m_shader;
		GLuint m_VAO;

		std::vector<glm::vec3> m_pos;
		std::vector<glm::vec3> m_nor;
		std::vector<glm::vec2> m_tex;
		std::size_t m_numberOfVert;

		void m_init();

	public:
		//constructors,desctructors
		Mesh(std::vector<util::Vertex>, std::size_t,Shader *shader);
		Mesh(const char* modelPath, Shader* shader);
		Mesh(Shader *);
		~Mesh() {}

		//openGL
		virtual void bind();
		void unbind();

		//Component
		void operation() override;
		inline std::size_t getCount() override { return m_numberOfVert; }
		inline bool isComposite() override { return false; }
		inline void move(float delta, MoveDirection moveDirection, glm::vec3 lookPositon = glm::vec3(0), glm::vec3 upVector = glm::vec3(0))override {}
		inline GLint getID()override { return m_ID; }
		inline void newScale() override { return; }

		//getters, setters
		inline std::size_t getNumberOfVert() { return this->m_numberOfVert; }
		inline void setShader(Shader *shader) { this->m_shader = shader; }

		//other
		void updateModel(glm::mat4&);
		virtual bool addTexture(const char* path);
		bool loadFromObj(const char* filePath);

};

