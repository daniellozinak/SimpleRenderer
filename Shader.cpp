#include "Shader.h"
#include "ShaderLoader.h"



#include <stdexcept>



Shader::Shader(const char*vertexPath, const char*fragmentPath){
	ShaderLoader shaderLoader;
	this->m_id = shaderLoader.loadShader(vertexPath, fragmentPath);
}

Shader::~Shader() {}

void Shader::sendUniform(const char* name, glm::mat4 data)
{
		GLuint m_matID = glGetUniformLocation(this->m_id, name);


	if (m_matID >= 0)
	{
		glUniformMatrix4fv(m_matID, 1, GL_FALSE, &data[0][0]);
		//glProgramUniform4fv(this->m_id, m_matID, 1, GL_FALSE, &data[0][0]);
	}
	else {
		printf("Uniform name not found\n");
		system("pause");
	}
}

void Shader::sendUniform(const char*name, glm::vec4 data)
{
	GLuint m_matID = glGetUniformLocation(this->m_id, name);

	if (m_matID >= 0)
	{
		glUniform4f(m_matID, data.x, data.y, data.z, data.w);
	}
	else {
		printf("Uniform name not found\n");
		system("pause");
	}
}

void Shader::sendUniform(const char*name, glm::vec3 data)
{
	GLuint m_matID = glGetUniformLocation(this->m_id, name);

	if (m_matID >= 0)
	{
		glUniform3f(m_matID, data.x, data.y, data.z);
	}
	else {
		printf("Uniform name not found\n");
		system("pause");
	}
}

void Shader::sendUniform(const char*name, float data)
{
	GLuint m_matID = glGetUniformLocation(this->m_id, name);

	if (m_matID >= 0)
	{
		glUniform1f(m_matID, data);
	}
	else {
		printf("Uniform name not found\n");
		system("pause");
	}
}


void Shader::bind() {
	glUseProgram(this->m_id);
}

void Shader::unbind() {
	glUseProgram(0);
}

void Shader::update(const char*uniformName, glm::mat4 data)
{
	this->sendUniform(uniformName, data);
}