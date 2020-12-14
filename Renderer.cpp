#include "Renderer.h"
#include "ComponentManager.h"#
#include "Cubemap.h"
#include "CallbackData.h"
#include "DemoScene.h"

Renderer::Renderer()
{
	DemoScene* scene = new DemoScene();
	setScene(scene);
	CallbackData::getInstance().scene = scene;
	scene->initScene();
}

void Renderer::render()
{
	this->clearBuffer();	this->enableStencil();
	glDepthFunc(GL_LESS);
	for (Component *component : ComponentManager::getInstance().getObjects())
	{
		//bind shader
		//bind VAO
		//draw
		component->update();
		if (!component->isComposite()) {
			glStencilFunc(GL_ALWAYS, component->getID(), 0xFF);
			glDrawArrays(GL_TRIANGLES, 0, component->getCount());
		}
	}

	if (m_scene != nullptr)
	{
		glDisable(GL_STENCIL_TEST);
		glDepthFunc(GL_LEQUAL);
		m_scene->bindSkyBox();

		glDrawArrays(GL_TRIANGLES, 0, 36);
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
