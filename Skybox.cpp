#include "Skybox.h"


std::string files[] = {
		"./Textures/cubemap/ocean_skybox/negx.jpg",
		"./Textures/cubemap/ocean_skybox/posx.jpg",
		"./Textures/cubemap/ocean_skybox/posy.jpg",
		"./Textures/cubemap/ocean_skybox/negy.jpg",
		"./Textures/cubemap/ocean_skybox/negz.jpg",
		"./Textures/cubemap/ocean_skybox/posz.jpg"
};

Skybox::Skybox()
{
	m_shader = new Shader(VERTEX_SHADER, FRAGMENT_SHADER);
	m_mesh = new Mesh(OBJ_PATH, m_shader);
	m_cubemap = new Cubemap(files, 0);
}

Skybox::~Skybox() {}

void Skybox::bind(glm::mat4 view, glm::mat4 project)
{
	m_shader->bind();
	m_mesh->bind();
	m_cubemap->bind();

	m_shader->sendUniform("modelMatrix", glm::mat4(1.0));
	m_shader->sendUniform("viewMatrix", glm::mat3(view));
	m_shader->sendUniform("projectionMatrix", project);
}