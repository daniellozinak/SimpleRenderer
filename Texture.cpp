#include "Texture.h"


Texture::Texture(GLenum type, GLuint textureUnit)
{
	m_type = type;
	m_textureUnit = textureUnit;

	glGenTextures(1, &m_id);
	glBindTexture(m_type, m_id);

	glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(type, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

Texture::~Texture() {
	glDeleteTextures(1, &m_id);
}

void Texture::bind()
{
	glActiveTexture(GL_TEXTURE0 + m_textureUnit);
	glBindTexture(m_type, m_id);
}

void Texture::unbind()
{
	glActiveTexture(0);
	glBindTexture(m_type, 0);
}