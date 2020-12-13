#include "DemoScene.h"
#include "Texture2D.h"
#include "Terrain.h"
#include "DirectionalLight.h"
#include "ObjectGenerator.h"
#include "PointLight.h"

#include "data_loader.hpp"

DemoScene::DemoScene():Scene()
{
	m_default = new Shader("./VertexShader.glsl", "./FragmentShaderPhongPoint.glsl");
	m_texture = new Shader("./VertexShader.glsl", "./FragmentShaderPhongPointTexture.glsl");

	m_tree = new Mesh("./Objects/MapleTreeStem.obj", m_texture);
	m_leaves = new Mesh("./Objects/MapleTreeLeaves.obj", m_default);

	Texture2D* treeTexture = new Texture2D(1, "./Textures/maple_bark.png", 1000, 1000);
	m_tree->addTexture(treeTexture);
	
}

void DemoScene::initScene()
{
	Scene::initScene(); 
	m_spotCamera = new SpotCamera(glm::vec3(-4, 0, 0), glm::vec3(4, 3, 1), glm::vec3(0, 1, 0));
	setCamera(m_spotCamera);

	Shader* terrainShader = new Shader("./VertexShader.glsl", "./FragmentShaderColorTerrain.glsl");

	addShader(m_default);
	addShader(m_texture);
	addShader(terrainShader);

	std::vector<util::Vertex> sphere = loadSphere();

	Mesh* cube = new Mesh("./Objects/skybox.obj", m_default);
	Object* cubeObject = new Object();
	cubeObject->add(cube);

	Terrain* terrain_plane_mesh = new Terrain(100,100,10,10,0.5, terrainShader);

	Object* terrain = new Object();
	terrain->setPosition(glm::vec3(-200,-2,-200));
	terrain->setScale(glm::vec3(100));
	terrain->add(terrain_plane_mesh);


	Mesh* ball = new Mesh(sphere, sphere.size(), m_default);
	Object* ballObj = new Object();
	ballObj->add(ball);

	Object* ballObje = new Object();
	Mesh* anotherBall = ball->clone();
	anotherBall->generateID();
	ballObje->add(anotherBall);
	ballObje->setPosition(glm::vec3(4, 3, 1));


	DirectionalLight* spotik = new DirectionalLight(glm::vec3(5));
	PointLight* direct = new PointLight(glm::vec3(5),0.2f,0.5f,0.3f);
	addLight(m_spotCamera->getLight());
	//addLight(spotik);

	
}

Object* DemoScene::createNewObject(std::vector<util::Vertex> vertex, glm::vec3 position)
{
	if (m_default == nullptr || m_texture == nullptr || m_tree == nullptr || m_leaves == nullptr) { return nullptr; }
	Mesh* tree_clone = m_tree->clone();
	Mesh* leaves_clone = m_leaves->clone();
	tree_clone->generateID();
	leaves_clone->generateID();
	return ObjectGenerator::getInstance().getRandomTree(position, m_texture, m_default, tree_clone, leaves_clone);
}
