#pragma once


#include "Scene.h"
#include <GLFW/glfw3.h> 

class Renderer
{
	private:
		void clearBuffer();
	public:	
		void enableDepth();
		void enableStencil();
		void render();
		Renderer();
};

