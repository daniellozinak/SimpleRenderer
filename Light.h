#pragma once
#include "ISubject.h"
#include <glm/vec3.hpp>

enum LightType {
	Point,
	Directional,
	Spot
};


class Light : public ISubject
{
	private:
		std::string m_id;
		glm::vec3 m_position;
	public:
		Light(glm::vec3 position,std::string id);
		~Light();

		void notify() override;

		inline glm::vec3 getPosition() { return m_position; }

};

