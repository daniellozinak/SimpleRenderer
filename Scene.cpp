#include "Scene.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "DirectionalLight.h"
#include "data_loader.hpp"
#include "CallbackData.h"
#include "Terrain.h"


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
	Light *tempLight = light;
	if (type == LightType::Point) { tempLight = static_cast<PointLight*>(light); }
	else if(type == LightType::Directional){}
	else if (type == LightType::Spot) { tempLight = static_cast<SpotLight*>(light); }

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

Object *Scene::createNewObject(std::vector<util::Vertex> vertex, glm::vec3 position)
{
	assert(m_shaders.at(0));
	Shader* defaultShader = m_shaders.at(0);
	Object *newObject = new Object();
	Mesh *mesh = new Mesh(vertex,vertex.size(), defaultShader);
	newObject->add(mesh);
	newObject->setPosition(position);

	return newObject;
}

void Scene::bindSkyBox()
{
	if (m_skybox == nullptr) { return; }
	m_skybox->bind(m_camera->getView(), m_camera->getProjection());
}

void Scene::initScene()
{
	std::vector<util::Vertex>vert_plain = loadPlain();
	std::vector<util::Vertex>vert_sphere = loadSphere();

	Shader* mShaderTexture = new Shader("./VertexShader.glsl", "./FragmentShaderPhongPointTexture.glsl");
	Shader* mShaderSkyBox = new Shader("./VertexShaderSkyBox.glsl", "./FragmentShaderSkyBox.glsl");

	Camera* m_camera = new Camera(glm::vec3(-4, -3, 0), glm::vec3(4, 3, 1), glm::vec3(0, 1, 0));
	PointLight* pointLight = new PointLight(glm::vec3(15), 0.002f, .03f, 0.0f);
	DirectionalLight* directionLight = new DirectionalLight(glm::vec3(8.0, 3.0, -2.0));
	SpotLight* spotLight = new SpotLight(glm::vec3(5.0f), glm::vec3(1.0, 1.0, 1.0), 0.55f);


	this->setCamera(m_camera);
	this->addShader(mShaderTexture);
	this->addShader(mShaderSkyBox);

	//Mesh* sphere = new Mesh(vert_sphere, vert_sphere.size(), mShaderPhong);
	//Mesh *worker = new Mesh(vert_worker, vert_worker.size(), mShaderPhong);
	//Mesh *suzi = new Mesh(vert_suzi, vert_suzi.size(), mShaderPhong);
	//Mesh *box = new Mesh(vert_box, vert_box.size(), mShaderPhong);
	/*Mesh* plain = new Mesh(vert_plain, vert_plain.size(), mShaderPhong);*/

	/*Mesh* pln = new Mesh(vert_plain, vert_plain.size(), mShaderTexture);
	pln->addTexture("./Textures/mino.png");*/

	//create skybox
	Cubemap* skybox = new Cubemap("./Objects/skybox.obj", mShaderSkyBox);
	skybox->load();

	Terrain* terrain_plane_mesh = new Terrain(250,250,8,8,0.7);
	this->addShader(terrain_plane_mesh->getShader());
	//terrain_plane_mesh->addTexture("./Textures/mino.png");

	//add skybox
	this->setSkyBox(skybox);

	/*scene->addMesh(sphere);
	scene->addMesh(worker);
	scene->addMesh(suzi);
	scene->addMesh(box);*/


	/*Object* ball = new Object();
	ball->setPosition(glm::vec3(8.0, 1.0, -2.0));
	ball->add(sphere);*/


	/*Object* plainObject = new Object();
	plainObject->setPosition(glm::vec3(8.0, 2.0, 2.0));
	plainObject->add(pln);*/


	//add lights after all the shaders have been added
	//this->addLight(spotLight, LightType::Spot);
	//this->addLight(directionLight, LightType::Directional);
	this->addLight(pointLight, LightType::Point);

	Object* terrain = new Object();
	terrain->setPosition(glm::vec3(2));
	terrain->add(terrain_plane_mesh);
}

