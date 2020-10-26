#include "Scene.h"


Scene::Scene()
{
	m_camera = new Camera(glm::vec3(-4, -3, 0), glm::vec3(4, 3, 1), glm::vec3(0, 1, 0));
	this->m_lightposition = glm::vec3(0, 0, 0);
}

Scene::~Scene(){}

void Scene::addObject(Object &object)
{
	m_objectmanager.addObject(object);
}

void Scene::addObject(Object &object, glm::vec3 initialPosition)
{
	m_objectmanager.addObject(object);
	object.move(initialPosition);
}

void Scene::addShader(Shader *shader)
{
	this->m_camera->attach(shader);
	shader->sendUniform(LIGHT_POSITION, m_lightposition);
}

void Scene::removeObject(Object &object)
{
	this->removeObject(object);
}

void Scene::removeShader(Shader *shader)
{
	this->m_camera->detach(shader);
}

void Scene::attachShaderToObject(Object&objcet, Shader*shader)
{
	objcet.setShader(shader);
}


void Scene::draw()
{
	this->m_objectmanager.draw();
}