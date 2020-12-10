#include "Texture2D.h"
#include "SOIL.h"
#include <stdlib.h>

Texture2D::Texture2D(GLuint textureUnit, const char* filepath,int width, int height) : Texture(GL_TEXTURE_2D,textureUnit)
{
	m_image = SOIL_load_image(filepath, &width, &height, NULL, SOIL_LOAD_RGBA);

	if (m_image)
	{
		glTexImage2D(getType(), 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_image);
	}
	else { exit(1); }

	glBindTexture(getType(), 0);
	SOIL_free_image_data(m_image);
}
