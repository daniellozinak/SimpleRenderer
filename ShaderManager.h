#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h> 

#include <stdio.h>

#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
//zle, Shader

class ShaderManager
{
public:
	ShaderManager(const ShaderManager&) = delete;
	static ShaderManager &getInstance();


	void createShaderVertex(const char*&);
	void createShaderFragment(const char*&);
	void link();


	void checkStatus();

	void sendUniform(const char *, glm::mat4&);

	void useProgram();

	// use shader metoda tu

private:
	GLuint m_id;

	GLuint m_vertexS;
	GLuint m_fragmentS;

	static ShaderManager m_instance;

	void createShader(GLuint &, const char*&, GLenum);

	ShaderManager();
	~ShaderManager();
};