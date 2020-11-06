#include "Scene.h"


Scene::Scene()
{
	m_camera = new Camera(glm::vec3(-4, -3, 0), glm::vec3(4, 3, 1), glm::vec3(0, 1, 0));
	this->m_lightposition = glm::vec3(0, 0, 0);
}

Scene::~Scene(){}


void Scene::addShader(Shader *shader)
{
	this->m_camera->attach(shader);
	shader->sendUniform(LIGHT_POSITION, m_lightposition);
	this->m_camera->update();
}

void Scene::setCamera(Camera *camera)
{
	m_camera = camera;
}

void Scene::setLight(glm::vec3 light)
{
	m_lightposition = light;
}

void Scene::removeShader(Shader *shader)
{
	this->m_camera->detach(shader);
}


