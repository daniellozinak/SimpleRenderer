#pragma once

#include <vector>
#include "Shader.h"
#include "Camera.h"
#include "Object.h"
#include "Mesh.h"
#include "Light.h"
#include "Cubemap.h"

#include <vector>

#define VERTEX_SHADER "./VertexShader.glsl"
#define FRAGMENT_SHADER_L "./FragmentShaderLambert.glsl"
#define FRAGMENT_SHADER_P "./FragmentShaderPhong.glsl"
#define FRAGMENT_SHADER_S "./FragmentShaderStatic.glsl"

#define LIGHT_POSITION "lightPosition"

class Scene
{
	private:
		Camera *m_camera;

		std::vector<Light*> m_ligths;

		std::vector<Shader*> m_shaders;
		std::vector<Mesh*> m_meshes;

		Light *tempLight;
		Cubemap* m_skybox;

	public:
		Scene();
		~Scene();

		void addShader(Shader*);
		void addShader(const char*, const char*);
		void setCamera(Camera*);
		void addMesh(Mesh*);
		void addLight(Light *light, LightType type);

		inline void setSkyBox(Cubemap* skybox) { m_skybox = skybox; }

		void bindSkyBox();

		Object *createNewObject(std::vector<util::Vertex> vertex,glm::vec3 position);
		
		void removeShader(Shader *);
		

};

