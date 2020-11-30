#include "Renderer.h"
#include "ComponentManager.h"#
#include "Cubemap.h"

Renderer::Renderer()
{
}

void Renderer::render()
{
	this->clearBuffer();	this->enableStencil();
	for (Component *component : ComponentManager::getInstance().getObjects())
	{
		//bind shader
		//bind VAO
		//draw
		component->operation();
		if (!component->isComposite()) {
			glStencilFunc(GL_ALWAYS, component->getID(), 0xFF);
			glDrawArrays(GL_TRIANGLES, 0, component->getCount());
		}
	}

	if (m_scene != nullptr)
	{
		m_scene->bindSkyBox();
	}
}


void Renderer::enableDepth()
{
	glEnable(GL_DEPTH_TEST);
}

void Renderer::enableStencil()
{
	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
}

void Renderer::clearBuffer()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT| GL_STENCIL_BUFFER_BIT);
}
