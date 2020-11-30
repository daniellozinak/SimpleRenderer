#pragma once


#include "Scene.h"
#include <GLFW/glfw3.h> 

class Renderer
{
	private:
		void clearBuffer();
		Scene* m_scene = nullptr;
	public:	
		void enableDepth();
		void enableStencil();
		void render();
		inline void setScene(Scene* scene) { m_scene = scene; }
		Renderer();
};

