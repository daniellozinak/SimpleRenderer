#pragma once
#include "ISubject.h"
#include <glm/vec3.hpp>

enum LightType {
	Point,
	Directional,
	Spot
};

#define DIRECTIONAL 0
#define POINT 1
#define SPOT 2

#define LIGHT_TYPE_UNIFROM ".lightType"
#define LIGHT_COUNT_UNIFROM "lightCount"


class Light : public ISubject
{
	private:
		std::string m_id;

		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
	public:
		Light(std::string id);
		~Light();

		void notify() override;

		inline std::string getID() { return m_id; }

};

