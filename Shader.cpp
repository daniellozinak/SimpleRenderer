#include "Shader.h"
#include "Camera.h" 



#include <stdexcept>


Shader::Shader(Camera* camera)
{
	this->m_camera = camera;
}

Shader::Shader() {}

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

void Shader::linkProgram(const char* vertexShaderCode, const char* fragmentShaderCode) {
	this->m_id = glCreateProgram();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderCode, NULL);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderCode, NULL);
	glCompileShader(fragmentShader);

	glAttachShader(this->m_id, vertexShader);
	glAttachShader(this->m_id, fragmentShader);

	glLinkProgram(this->m_id);


	GLint status;
	glGetProgramiv(this->m_id, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(this->m_id, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(this->m_id, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "Linker failure: %s\n", strInfoLog);
		delete[] strInfoLog;
		throw std::invalid_argument("shader error");
	}

	this->bind();
}

void Shader::bind() {
	glUseProgram(this->m_id);
}

void Shader::unbind() {
	glUseProgram(0);
}

void Shader::setCamera(Camera*& c) {
	this->m_camera = c;
}

Camera *Shader::getCamera() { return this->m_camera; }

void Shader::update(const char*uniformName, glm::mat4 data)
{
	this->sendUniform(uniformName, data);
}