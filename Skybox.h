#pragma once
#include "Mesh.h"
#include "Cubemap.h"
#include "Shader.h"

#define VERTEX_SHADER "VertexShaderSkyBox.glsl"
#define FRAGMENT_SHADER "FragmentShaderSkyBox.glsl"

#define OBJ_PATH "./Objects/skybox.obj"

class Skybox
{
	private:
		Mesh* m_mesh;
		Shader* m_shader;
		Cubemap* m_cubemap;
	public:
		Skybox();
		~Skybox();

		void bind(glm::mat4 view, glm::mat4 project);

		inline Shader* getShader() { return m_shader; }
};

