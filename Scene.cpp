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
	return ObjectGenerator::getInstance().getRandomObject(position,defaultShader);
}

void Scene::bindSkyBox()
{
	/*if (m_skybox == nullptr) { return; }
	m_skybox->bind(m_camera->getView(), m_camera->getProjection());*/
}

void Scene::initScene()
{
	std::vector<util::Vertex>vert_plain = loadPlain();
	std::vector<util::Vertex>vert_sphere = loadSphere();

	Shader* shader = new Shader("./VertexShader.glsl", "./FragmentShaderPhongPoint.glsl");
	Shader* mShaderTexture = new Shader("./VertexShader.glsl", "./FragmentShaderPhongPointTexture.glsl");
	Shader* mShaderSkyBox = new Shader("./VertexShaderSkyBox.glsl", "./FragmentShaderSkyBox.glsl");

	Camera* m_camera = new Camera(glm::vec3(-4, -3, 0), glm::vec3(4, 3, 1), glm::vec3(0, 1, 0));
	PointLight* pointLight = new PointLight(glm::vec3(15), 0.002f, .03f, 0.0f);
	DirectionalLight* directionLight = new DirectionalLight(glm::vec3(8.0, 3.0, -2.0));
	SpotLight* spotLight = new SpotLight(glm::vec3(5.0f), glm::vec3(1.0, 1.0, 1.0), 0.55f);


	this->setCamera(m_camera);
	this->addShader(shader);
	this->addShader(mShaderTexture);
	this->addShader(mShaderSkyBox);

	//Mesh* sphere = new Mesh(vert_sphere, vert_sphere.size(), mShaderPhong);
	//Mesh *worker = new Mesh(vert_worker, vert_worker.size(), mShaderPhong);
	//Mesh *suzi = new Mesh(vert_suzi, vert_suzi.size(), mShaderPhong);
	//Mesh *box = new Mesh(vert_box, vert_box.size(), mShaderPhong);

	std::string files[] = {
		"./Textures/cubemap/negx.jpg",
		"./Textures/cubemap/posx.jpg",
		"./Textures/cubemap/posy.jpg",
		"./Textures/cubemap/negy.jpg",
		"./Textures/cubemap/negz.jpg",
		"./Textures/cubemap/posz.jpg"
	};

	

	Mesh* plain0 = new Mesh(vert_plain, vert_plain.size(), mShaderTexture);
	Texture2D * me = new Texture2D(0, "./Textures/me.png",200,200);
	plain0->addTexture(me);

	Mesh* plain1 = new Mesh(vert_plain, vert_plain.size(), mShaderTexture);
	Texture2D* mino = new Texture2D( 1, "./Textures/mino.png", 200, 200);
	plain1->addTexture(mino);

	Mesh* plain2 = new Mesh(vert_plain, vert_plain.size(), mShaderTexture);
	Texture2D* danko = new Texture2D( 2, "./Textures/danko.png", 200, 200);
	plain2->addTexture(danko);

	Mesh* skybox = new Mesh("./Objects/skybox.obj", mShaderSkyBox);
	Cubemap* skyboxCubemap = new Cubemap(files,3);
	skybox->addTexture(skyboxCubemap);


	Mesh* tree = new Mesh("./Objects/lowpoly_tree.obj", shader);





	/*Terrain* terrain_plane_mesh = new Terrain(200,200,10,10,0.4);
	this->addShader(terrain_plane_mesh->getShader());*/
	//terrain_plane_mesh->addTexture("./Textures/mino.png");

	this->addLight(directionLight, LightType::Directional);

	/*Object* terrain = new Object();
	terrain->setPosition(glm::vec3(2));
	terrain->setModelMatatrix(glm::scale(terrain->getModelMatrix(), glm::vec3(100)));
	terrain->add(terrain_plane_mesh);*/

	Object* minoObject = new Object();
	minoObject->setPosition(glm::vec3(-11.0f, -2.0f, 6.0f));
	minoObject->add(plain1);

	Object* meObject = new Object();
	meObject->setPosition(glm::vec3(-10.0f,-2.0f, 5.0f));
	meObject->add(plain0);

	Object* dankoobject = new Object();
	dankoobject->setPosition(glm::vec3(-9.0f, -3.0f, 5.0f));
	dankoobject->add(plain2);

	Object* box = new Object();
	box->setPosition(glm::vec3(-15.0f, -3.0f, 5.0f));
	box->add(skybox);

	

	/*Object* testCube = new Object();
	testCube->add(skybox);*/
	
}

