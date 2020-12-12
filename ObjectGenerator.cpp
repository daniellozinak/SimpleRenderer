#include "ObjectGenerator.h"
#include "Texture2D.h"

ObjectGenerator ObjectGenerator::m_instance;


ObjectGenerator& ObjectGenerator::getInstance() { return m_instance; }

ObjectGenerator::ObjectGenerator() {}



Object* ObjectGenerator::getRandomObject(glm::vec3 position, Shader* shader)
{

	Object* newObject = new Object();

	Mesh* newMesh = new Mesh(m_meshPath, shader);
	newObject->add(newMesh);
	newObject->setPosition(position);
	newObject->setRotate(m_randomRotation(), m_rotationAxis);
	newObject->setScale(m_randomScale());

	return newObject;
}

Object* ObjectGenerator::getRandomTree(glm::vec3 position, Shader* shaderTrunk, Shader* shaderLeaves,Mesh*tree,Mesh *leaves)
{
	Object* newObject = new Object();



	Object* treeObject0 = new Object();
	treeObject0->add(tree);


	Object* leavesObject = new Object();
	leavesObject->add(leaves);

	newObject->add(treeObject0);
	newObject->add(leavesObject);

	newObject->setPosition(position);


	treeObject0->setRotate(m_randomRotation(), m_rotationAxis);
	treeObject0->setScale(m_randomScale());

	leavesObject->setRotate(m_randomRotation(), m_rotationAxis);
	leavesObject->setScale(m_randomScale());

	return newObject;
}

float ObjectGenerator::m_randomRotation()
{
	return m_randomFloat() * 3.14f;
}

glm::vec3 ObjectGenerator::m_randomScale()
{
	float x = m_minScale + m_randomFloat() * (m_maxScale - m_minScale);
	float y = m_minScale + m_randomFloat() * (m_maxScale - m_minScale);
	float z = m_minScale + m_randomFloat() * (m_maxScale - m_minScale);

	return glm::vec3(x, y, z);
}

float ObjectGenerator::m_randomFloat()
{
	return static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}