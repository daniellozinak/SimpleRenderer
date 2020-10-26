#pragma once

#include <vector>

#include "ObjectManager.h"
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
		ObjectManager &m_objectmanager = ObjectManager::getInstance();
		Camera *m_camera;
		glm::vec3 m_lightposition;

	public:
		Scene();
		~Scene();

		void addObject(Object &);
		void addObject(Object &, glm::vec3 initialPosition);
		void addShader(Shader *);

		void draw();
		
		void removeObject(Object &);
		void removeShader(Shader *);

		void attachShaderToObject(Object&, Shader*);

};

