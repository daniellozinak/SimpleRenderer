#pragma once

#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <list>
#include <math.h>

#include "glm/gtx/string_cast.hpp"

#include "ISubject.h"
#include "IObserver.h"


# define M_PI 3.14159265358979323846

class Shader; //Shader declaration due to cross reference
class Camera : public ISubject
{
public:
	Camera(glm::vec3 center, glm::vec3 eye, glm::vec3 up, Shader*);
	~Camera();

	//ISubject method
	void attach(IObserver *oberver) override;
	void detach(IObserver *oberver) override;
	void notify() override;

	glm::mat4 getView();
	glm::mat4 getProjection();
	void changeTarget();
	void setShader(Shader*);
	void setEye(glm::vec3);
	void setCenter(glm::vec3);
	void setUp(glm::vec3);
	void setProjection(glm::mat4);

	void moveLeft(float);
	void moveRight(float);
	void moveUp(float);
	void moveDown(float);


	void update();

private:

	std::list<IObserver*> m_observers;

	glm::vec3 m_center;
	glm::vec3 m_eye;
	glm::vec3 m_up;

	glm::mat4 m_projection;

	float m_horizontalAngle = 0.0f;
	float m_verticalAngle = 0.0f;

	const int m_speed = 2;

	Shader *m_shader;
};