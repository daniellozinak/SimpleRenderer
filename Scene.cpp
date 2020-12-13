#include "Scene.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "DirectionalLight.h"
#include "data_loader.hpp"
#include "CallbackData.h"
#include "Terrain.h"
#include "ObjectGenerator.h"
#include "Texture2D.h"
#include "Mesh.h"
#include <glm/mat4x4.hpp>
#include "SpotCamera.h"


Scene::Scene()
{
	initScene();
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

void Scene::addLight(Light *light)
{
	Light *tempLight = light;

	if (!tempLight->isIdSet()) { tempLight->setId(m_lightCount); }
	m_lightCount++;

	for (Shader * shader : m_shaders)
	{
		tempLight->attach(shader);
		shader->sendUniform(LIGHT_COUNT_UNIFROM, m_lightCount);
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
	CallbackData::getInstance().camera = camera;
}


void Scene::removeShader(Shader *shader)
{
	this->m_camera->detach(shader);
	for (Light *light : m_ligths)
	{
		light->detach(shader);
	}
}

void Scene::bindSkyBox()
{
	if (m_skybox == nullptr) { return; }
	m_skybox->bind(m_camera->getView(), m_camera->getProjection());
}

void Scene::initScene()
{
	m_camera = new Camera(glm::vec3(-4, 0, 0), glm::vec3(4, 3, 1), glm::vec3(0, 1, 0));
	setCamera(m_camera);

	Skybox* skybox = new Skybox();
	this->addShader(skybox->getShader());
	m_skybox = skybox;
}

