#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h> 
#include <stdio.h>
#include <iostream>

#include <glm/mat4x4.hpp> // glm::mat4


#include "ISubject.h"
#include "IObserver.h"

class Camera; //Camera declaration due to cross reference
class Shader : public IObserver
{
public:
	Shader(Camera *);
	Shader();
	~Shader();

	//observer method
	void update(const char*, glm::mat4) override;

	void sendUniform(const char*, glm::mat4);
	void sendUniform(const char*, glm::vec4);
	void sendUniform(const char*, glm::vec3);
	void sendUniform(const char*, float);

	void linkProgram(const char* vertex, const char*frag);

	void bind();
	void unbind();

	void setCamera(Camera*&);
	Camera *getCamera();

private:
	GLuint m_id;

	Camera *m_camera;
};