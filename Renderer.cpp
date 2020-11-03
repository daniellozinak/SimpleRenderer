#include "Renderer.h"

Renderer::Renderer()
{
	m_scene = new Scene();
}

void Renderer::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_scene->draw();
}


void Renderer::enableDepth()
{
	glEnable(GL_DEPTH_TEST);
}

void Renderer::setScene(Scene* scene)
{
	m_scene = scene;
}