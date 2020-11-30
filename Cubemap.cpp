#include "Cubemap.h"
#include "SOIL.h"

Cubemap::Cubemap(const char* modelPath, Shader* shader) : Mesh(modelPath,shader)
{
	m_sideTexturesPath  = {
		"./Textures/cubemap/negx.jpg",
		"./Textures/cubemap/posx.jpg",
		"./Textures/cubemap/posy.jpg",
		"./Textures/cubemap/negy.jpg",
		"./Textures/cubemap/negz.jpg",
		"./Textures/cubemap/posz.jpg"
	};
}


bool Cubemap::load()
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, this->m_TextureID);


	
	m_TextureID = SOIL_load_OGL_cubemap
	(
		m_sideTexturesPath.at(0).c_str(),
		m_sideTexturesPath.at(1).c_str(),
		m_sideTexturesPath.at(2).c_str(),
		m_sideTexturesPath.at(3).c_str(),
		m_sideTexturesPath.at(4).c_str(),
		m_sideTexturesPath.at(5).c_str(),
		SOIL_LOAD_RGB,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS
	);


	if (m_TextureID == 0)
	{
		std::cout << "Cant load cubemap " << std::endl;
		exit(1);
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);


	return true;
}

void Cubemap::bind(glm::mat4 view, glm::mat4 project)
{
	glDepthFunc(GL_LEQUAL);
	m_shader->bind();
	m_shader->sendUniform("modelMatrix", glm::mat4(1.0));
	m_shader->sendUniform("viewMatrix", glm::mat3(view)); //to remove translation
	m_shader->sendUniform("projectionMatrix", project);
	
	glBindVertexArray(m_VAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, this->m_TextureID);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glDepthFunc(GL_LESS);
}