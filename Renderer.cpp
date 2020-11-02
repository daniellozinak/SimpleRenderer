#include "Renderer.h"

Renderer::Renderer()
{
	m_scene = new Scene();
}

void Renderer::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (std::size_t i = 0; i < m_scene->getObjectManager().getSize(); i++)
	{
		Object o = m_scene->getObjectManager().getNext();
		o.draw();
	}
}


void Renderer::enableDepth()
{
	glEnable(GL_DEPTH_TEST);
}

void Renderer::setScene(Scene* scene)
{
	m_scene = scene;
}