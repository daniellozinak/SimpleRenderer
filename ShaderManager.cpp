#include "ShaderManager.h"

ShaderManager ShaderManager::m_instance;


ShaderManager::ShaderManager()
{
	//this->id = glCreateProgram();
}


ShaderManager::~ShaderManager()
{
}

ShaderManager &ShaderManager::getInstance() {

	return m_instance;
}

void ShaderManager::createShader(GLuint &shaderId, const char*&code, GLenum type) {
	shaderId = glCreateShader(type);
	glShaderSource(shaderId, 1, &code, NULL);
	glCompileShader(shaderId);
}

void ShaderManager::createShaderVertex(const char *& code)
{
	this->createShader(this->m_vertexS, code, GL_VERTEX_SHADER);
}

void ShaderManager::createShaderFragment(const char *& code)
{
	this->createShader(this->m_fragmentS, code, GL_FRAGMENT_SHADER);
}

void ShaderManager::link() {

	this->m_id = glCreateProgram();

	glAttachShader(this->m_id, m_vertexS);
	glAttachShader(this->m_id, m_fragmentS);
	glLinkProgram(this->m_id);
}

void ShaderManager::useProgram()
{
	glUseProgram(m_id);
}

void ShaderManager::checkStatus()
{
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
	}
}

void ShaderManager::sendUniform(const char* name, glm::mat4 &data)
{
	GLint uniformID = glGetUniformLocation(m_id, name);
	if (uniformID >= 0)
	{
		glUniformMatrix4fv(uniformID, 1, GL_FALSE, &data[0][0]);
	}
	else {
		printf("Uniform name not found\n");
		system("pause");
	}
}