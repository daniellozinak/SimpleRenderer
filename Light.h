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

		glm::vec3 m_ambient;
		glm::vec3 m_diffuse;
		glm::vec3 m_specular;


		bool m_isIdSet = false;
	public:
		Light(std::string id);
		Light();
		~Light();

		void notify() override;

		inline std::string getID() { return m_id; }
		void setId(int id);

		inline bool isIdSet() { return m_isIdSet; }

		inline void setAmbient(glm::vec3 ambient) { m_ambient = ambient; }
		inline void setDiffuse(glm::vec3 diffuse) { m_diffuse = diffuse; }
		inline void setSpecular(glm::vec3 specular) { m_specular = specular; }

};

