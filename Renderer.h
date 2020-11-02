#pragma once


#include "Scene.h"
#include <GLFW/glfw3.h> 

class Renderer
{
	private:
		Scene *m_scene;
	public:	
		void render();
		void enableDepth();
		void setScene(Scene*);
		Renderer();
};

