#include "Renderer.h"
#include "ComponentManager.h"

Renderer::Renderer()
{
}

void Renderer::render()
{
	this->clearBuffer();
	for (Component *component : ComponentManager::getInstance().getObjects())
	{
		//bind shader
		//bind VAO
		//draw
		component->operation();
		if (component->getCount() > 0) { // if getCount() == 0, Component is Object
			glDrawArrays(GL_TRIANGLES, 0, component->getCount());
		}
	}
}


void Renderer::enableDepth()
{
	glEnable(GL_DEPTH_TEST);
}

void Renderer::clearBuffer()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}