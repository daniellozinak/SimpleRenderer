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
	if (m_default == nullptr || m_texture == nullptr) { return nullptr; }
	Shader* defaultShader = m_shaders.at(0);
	Mesh* tree_clone = m_tree->clone();
	Mesh* leaves_clone = m_leaves->clone();
	tree_clone->generateID();
	leaves_clone->generateID();
	return ObjectGenerator::getInstance().getRandomTree(position, m_texture, m_default, tree_clone, leaves_clone);
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


	m_default = new Shader("./VertexShader.glsl", "./FragmentShaderPhongPoint.glsl");
	m_texture = new Shader("./VertexShader.glsl", "./FragmentShaderPhongPointTexture.glsl");
	Shader* mShaderSkyBox = new Shader("./VertexShaderSkyBox.glsl", "./FragmentShaderSkyBox.glsl");
	Shader* mShaderCubemap = new Shader("./VertexShaderCubemap.glsl", "./FragmentShaderCubemap.glsl");

	Camera* m_camera = new Camera(glm::vec3(-4, -3, 0), glm::vec3(4, 3, 1), glm::vec3(0, 1, 0));
	PointLight* pointLight = new PointLight(glm::vec3(15), 0.002f, .03f, 0.0f);
	DirectionalLight* directionLight = new DirectionalLight(glm::vec3(8.0, 3.0, -2.0));
	SpotLight* spotLight = new SpotLight(glm::vec3(5.0f), glm::vec3(1.0, 1.0, 1.0), 0.55f);


	this->setCamera(m_camera);
	this->addShader(m_default);
	this->addShader(m_texture);
	this->addShader(mShaderSkyBox);
	this->addShader(mShaderCubemap);

	//Mesh* sphere = new Mesh(vert_sphere, vert_sphere.size(), mShaderPhong);
	//Mesh *worker = new Mesh(vert_worker, vert_worker.size(), mShaderPhong);
	//Mesh *suzi = new Mesh(vert_suzi, vert_suzi.size(), mShaderPhong);
	//Mesh *box = new Mesh(vert_box, vert_box.size(), mShaderPhong);


	Skybox* skybox = new Skybox();
	this->addShader(skybox->getShader());
	m_skybox = skybox;

	m_tree = new Mesh("./Objects/MapleTreeStem.obj", m_texture);
	Texture2D* treeTexture = new Texture2D(1, "./Textures/maple_bark.png", 1000, 1000);
	m_tree->addTexture(treeTexture);
	m_leaves = new Mesh("./Objects/MapleTreeLeaves.obj", m_default);


	
	//Texture2D *treeTexture = new Texture2D(1, "./Textures/maple_bark.png",1000,1000);
	//tree->addTexture(treeTexture);


	//Mesh* leaves = new Mesh("./Objects/MapleTreeLeaves.obj", shader);

	

	Terrain* terrain_plane_mesh = new Terrain(400,400,20,20,0.5);
	this->addShader(terrain_plane_mesh->getShader());

	Object* terrain = new Object();
	terrain->setPosition(glm::vec3(-200,0,-200));
	terrain->setScale(glm::vec3(200));
	terrain->add(terrain_plane_mesh);

	//Object* treeObject0 = new Object();
	//treeObject0->add(tree);
	//treeObject0->setPosition(glm::vec3(0));

	//Object* treeObject1 = new Object();
	//treeObject1->add(tree);
	//treeObject1->setPosition(glm::vec3(10));

	//Object* treeObject2 = new Object();
	//treeObject2->add(tree);
	//treeObject2->setPosition(glm::vec3(4));

	//Object* treeObject3 = new Object();
	//treeObject3->add(tree);
	//treeObject3->setPosition(glm::vec3(10));

	//Object* treeObject4 = new Object();
	//treeObject4->add(tree);
	//treeObject4->setPosition(glm::vec3(15));

	//Object* leavesObject = new Object();
	//leavesObject->add(leaves);
	//


	this->addLight(directionLight, LightType::Directional);
	

	/*Object* testCube = new Object();
	testCube->add(skybox);*/
	
}

