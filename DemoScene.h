#pragma once
#include "Scene.h"
#include "Shader.h"
#include "Mesh.h"
#include "Object.h"
#include "SpotCamera.h"

class DemoScene : public Scene
{
private:
	Shader* m_default;
	Shader* m_texture;

	Mesh* m_tree;
	Mesh* m_leaves;

	SpotCamera* m_spotCamera;
public:
	DemoScene();
	Object* createNewObject(std::vector<util::Vertex> vertex, glm::vec3 position) override;
	void initScene() override;
};

