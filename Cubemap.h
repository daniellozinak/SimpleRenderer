#pragma once

#include "Texture.h"
#include <vector>
#include <string>
#include <glm/mat4x4.hpp>

class Cubemap : public Texture
{
	private:
		std::string  m_images[6];
	public:
		Cubemap(std::string  m_images[6], GLuint textureUnit);
};

