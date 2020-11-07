#pragma once

#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <list>
#include <math.h>

#include "glm/gtx/string_cast.hpp"

#include "ISubject.h"
#include "IObserver.h"
#include "IMovable.h"


# define M_PI 3.14159265358979323846

class Shader; //Shader declaration due to cross reference
class Camera : public ISubject,IMovable
{
	public:
		Camera(glm::vec3 center, glm::vec3 eye, glm::vec3 up);
		~Camera();

		//ISubject method
		void notify() override;
		void move(float delta, MoveDirection moveDirection, glm::vec3 lookPositon = glm::vec3(0)) override;

		glm::mat4 getView();
		glm::mat4 getProjection();
		inline glm::vec3 getLookDirection() { return this->m_eye - this->m_center; }

		void setEye(glm::vec3);
		void setCenter(glm::vec3);
		void setUp(glm::vec3);
		void setProjection(glm::mat4);

		void lookAround(float delta,float xDiff, float yDiff);

		void update();

	private:

		glm::vec3 m_center;
		glm::vec3 m_eye;
		glm::vec3 m_up;

		glm::mat4 m_projection;

		float m_horizontalAngle = 0.0f;
		float m_verticalAngle = 0.0f;

		const int m_speedlooking = 1;
};