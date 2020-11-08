#pragma once

#include <vector>
#include "Shader.h"
#include "Camera.h"
#include "Object.h"
#include "Mesh.h"

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
		//TODO 3: Add Light class as ISubject to Shader
		glm::vec3 m_lightposition;

		std::vector<Shader*> m_shaders;
		std::vector<Mesh*> m_meshes;

	public:
		Scene();
		~Scene();

		void addShader(Shader *);
		void setCamera(Camera *);
		void addMesh(Mesh *);
		void setLight(glm::vec3);

		Object *createNewObject(std::vector<util::Vertex> vertex,glm::vec3 position);
		
		void removeShader(Shader *);

};

