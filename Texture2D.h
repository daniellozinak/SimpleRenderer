#pragma once

#include "Texture.h"

class Texture2D : public Texture
{
private:
	unsigned char* m_image;
public:
	Texture2D(GLuint textureUnit, const char* filepath,int width,int height);
};

