#include "DemoScene.h"
#include "Texture2D.h"
#include "Terrain.h"
#include "DirectionalLight.h"
#include "ObjectGenerator.h"
#include "PointLight.h"
#include "Line.h"
#include "CurveObject.h"
#include "BezierCurve.h"

#include "data_loader.hpp"

DemoScene::DemoScene():Scene()
{
	m_default = new Shader("./VertexShader.glsl", "./FragmentShaderLeaves.glsl");
	m_texture = new Shader("./VertexShader.glsl", "./FragmentShaderPhong.glsl");

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


	Line *line = new Line(glm::vec3(0), glm::vec3(30.0f, 20.0f, 0.0f));

	std::vector<glm::vec3> points;
	points.push_back(glm::vec3(0,0,0));
	points.push_back(glm::vec3(20,50,0));
	points.push_back(glm::vec3(40,50,0));
	points.push_back(glm::vec3(60,0,0));
	BezierCurve* curve = new BezierCurve(points);

	Shader* terrainShader = new Shader("./VertexShader.glsl", "./FragmentShaderTerrain.glsl");
	Shader *blinn = new Shader("./VertexShader.glsl", "./FragmentShaderBlinn.glsl");


	addShader(m_default);
	addShader(m_texture);
	addShader(blinn);
	addShader(terrainShader);

	std::vector<util::Vertex> sphere = loadSphere();

	Mesh* sphereMesh = new Mesh(sphere,sphere.size(), blinn);
	CurveObject* cubeObject = new CurveObject(curve);
	cubeObject->add(sphereMesh);

	Mesh* anotherSphere = sphereMesh->clone();
	CurveObject* sphereObj = new CurveObject(line);
	sphereObj->add(anotherSphere);
	sphereObj->setPosition(glm::vec3(2));

	Terrain* terrain_plane_mesh = new Terrain(200,200,10,10,0.5, terrainShader);

	Object* terrain = new Object();
	terrain->setPosition(glm::vec3(-500,-6,-500));
	terrain->setScale(glm::vec3(200));
	terrain->add(terrain_plane_mesh);

	DirectionalLight* direct = new DirectionalLight(glm::vec3(5));
	direct->setAmbient(glm::vec3(0.01f));
	direct->setDiffuse(glm::vec3(0.4f));
	direct->setSpecular(glm::vec3(0.4f));
	addLight(m_spotCamera->getLight());
	addLight(direct);
	

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
