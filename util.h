
#pragma once
#include <GL/glew.h>
#include <iostream>
#include <vector>

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec2.hpp> // glm::vec2

namespace util {

	struct Vertex {
		glm::vec3 position;
		glm::vec3 color;
		glm::vec2 texture;
	};

}