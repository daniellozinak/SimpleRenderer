#pragma once

#include "Mesh.h"
#include <vector>
#include <string>
#include <glm/mat4x4.hpp>

class Cubemap : public Mesh
{
	private:
		std::vector<std::string>m_sideTexturesPath;
	public:
		Cubemap(const char* modelPath, Shader* shader);
		bool load();
		void bind(glm::mat4 view,glm::mat4 project);
};

