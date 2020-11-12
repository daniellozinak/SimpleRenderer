#include "Scene.h"


Scene::Scene()
{
	m_camera = new Camera(glm::vec3(-4, -3, 0), glm::vec3(4, 3, 1), glm::vec3(0, 1, 0));
	Light *light0 = new Light(glm::vec3(0),"lights[0]");
	Light *light1 = new Light(glm::vec3(15),"lights[1]");
	m_ligths.emplace_back(light0);
	m_ligths.emplace_back(light1);
}

Scene::~Scene(){}


void Scene::addShader(Shader *shader)
{
	m_shaders.emplace_back(shader);
	this->m_camera->attach(shader);


	for (Light *light : m_ligths)
	{
		light->attach(shader);
		light->notify();
	}
	this->m_camera->notify();
}

void Scene::addMesh(Mesh * mesh)
{
	m_meshes.emplace_back(mesh);
}

void Scene::setCamera(Camera *camera)
{
	m_camera = camera;
}


void Scene::removeShader(Shader *shader)
{
	this->m_camera->detach(shader);
	for (Light *light : m_ligths)
	{
		light->detach(shader);
	}
}

Object *Scene::createNewObject(std::vector<util::Vertex> vertex, glm::vec3 position)
{
	assert(m_shaders.at(0));
	Object *newObject = new Object();
	Mesh *mesh = new Mesh(vertex,vertex.size(),m_shaders.at(0));
	newObject->add(mesh);
	newObject->setPosition(position);

	return newObject;
}


