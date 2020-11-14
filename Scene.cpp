#include "Scene.h"
#include "PointLight.h"
#include "SpotLight.h"


Scene::Scene()
{
	m_camera = new Camera(glm::vec3(-4, -3, 0), glm::vec3(4, 3, 1), glm::vec3(0, 1, 0));
}

Scene::~Scene(){}


void Scene::addShader(Shader *shader)
{
	m_shaders.emplace_back(shader);
	this->m_camera->attach(shader);
	this->m_camera->notify();
}

void Scene::addShader(const char* vertexPath, const char*fragmentPath)
{
	Shader *newShader = new Shader(vertexPath, fragmentPath);
	m_shaders.emplace_back(newShader);
	m_camera->attach(newShader);

	m_camera->notify();
}

void Scene::addLight(Light *light,LightType type)
{
	this->tempLight = light;
	if (type == LightType::Point) { tempLight = static_cast<PointLight*>(light); }
	else if(type == LightType::Directional){}
	else if (type == LightType::Spot) { tempLight = static_cast<SpotLight*>(light); }

	for (Shader * shader : m_shaders)
	{
		tempLight->attach(shader);
	}
	tempLight->notify();
	
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


