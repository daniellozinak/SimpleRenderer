#pragma once

#include <vector>
#include "Shader.h"
#include "Camera.h"
#include "Object.h"

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

	public:
		Scene();
		~Scene();

		void addShader(Shader *);
		void setCamera(Camera *);
		void setLight(glm::vec3);
		
		void removeShader(Shader *);

};

