#include "Cubemap.h"
#include "SOIL.h"

Cubemap::Cubemap(std::string  m_images[6], GLuint textureUnit) : Texture(GL_TEXTURE_CUBE_MAP, textureUnit)
{
	setId(SOIL_load_OGL_cubemap
	(
		m_images[0].c_str(),
		m_images[1].c_str(),
		m_images[2].c_str(),
		m_images[3].c_str(),
		m_images[4].c_str(),
		m_images[5].c_str(),
		SOIL_LOAD_RGB,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS
	));

	glBindTexture(getType(), 0);
}


void Cubemap::bind()
{
	Texture::bind();
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
}
