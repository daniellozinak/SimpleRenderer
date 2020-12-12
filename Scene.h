#pragma once

#include <vector>
#include "Shader.h"
#include "Camera.h"
#include "Object.h"
#include "Mesh.h"
#include "Light.h"
#include "Cubemap.h"
#include "Skybox.h"

#include <vector>


#define LIGHT_POSITION "lightPosition"

class Scene
{
	private:
		Camera *m_camera;

		std::vector<Light*> m_ligths;
		std::vector<Shader*> m_shaders;
		std::vector<Mesh*> m_meshes;
		Skybox* m_skybox;
		int m_lightCount = 0;

		Shader* m_default;
		Shader* m_texture;

		Mesh* m_tree;
		Mesh* m_leaves;

	public:
		Scene();
		~Scene();

		void addShader(Shader*);
		void addShader(const char*, const char*);
		void setCamera(Camera*);
		void addMesh(Mesh*);
		void addLight(Light *light, LightType type);


		void bindSkyBox();

		Object *createNewObject(std::vector<util::Vertex> vertex,glm::vec3 position);
		
		void removeShader(Shader *);
		
		void initScene();
};

