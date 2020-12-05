#include "Terrain.h"
#include "glm/gtc/noise.hpp"
#include "glm/gtx/string_cast.hpp"
#include <vector>

Terrain::Terrain(Shader* shader, int xVertCount, int zVertCount) : Mesh(shader)
{
	m_width = 5;
	m_height = 5;
	m_xVertices = xVertCount;
	m_zVertices = zVertCount;
}

void Terrain::generatePlain()
{
	//init height
	const int y = 0;

	std::vector<glm::vec3> plain_points;

	float step_x = (float)m_width / (float)m_xVertices;
	float step_z = (float)m_height / (float)m_zVertices;

	for (float i = 0; i < (float)m_width; i+= step_x)
	{
		for (float j = 0; j < (float)m_height; j+= step_z)
		{
			float x = i;
			float z = j;
			glm::vec3 point = glm::vec3(x,y,z);

			plain_points.emplace_back(point);
		}
	}

	
	for (int i = 0; i < (int)plain_points.size(); i++)
	{
		glm::vec3 vertex1 = plain_points.at(i);
		glm::vec3 vertex2 = glm::vec3(plain_points.at(i).x + step_x, plain_points.at(i).y, plain_points.at(i).z);
		glm::vec3 vertex3 = glm::vec3(plain_points.at(i).x, plain_points.at(i).y, plain_points.at(i).z + step_z);
		glm::vec3 vertex4 = glm::vec3(plain_points.at(i).x + step_x, plain_points.at(i).y, plain_points.at(i).z + step_z);

		if (vertex1.x != m_width - step_x && vertex1.z != m_height - step_z)
		{
			m_pos.emplace_back(vertex1);
			m_pos.emplace_back(vertex2);
			m_pos.emplace_back(vertex3);

			m_pos.emplace_back(vertex4);
			m_pos.emplace_back(vertex3);
			m_pos.emplace_back(vertex2);
		}
	}

	m_numberOfVert = m_pos.size();
}

void Terrain::generateTerrain()
{
	generatePlain();
	for (int i = 0; i < m_numberOfVert; i++)
	{
		glm::vec2 vertex_xz = glm::vec2(m_pos.at(i).x, m_pos.at(i).z);
		float new_y = m_altitude * glm::perlin(vertex_xz);

		m_pos.at(i) = glm::vec3(m_pos.at(i).x, new_y, m_pos.at(i).z);

		//std::cout << glm::to_string(m_pos.at(i)) << std::endl;

	}


	for (int i = 0; i < m_numberOfVert; i +=3)
	{
		glm::vec3 vector1 = m_pos.at(i + 1) - m_pos.at(i);
		glm::vec3 vector2 = m_pos.at(i + 2) - m_pos.at(i);
		glm::vec3 new_normal = glm::cross(vector1, vector2);
		m_nor.emplace_back(new_normal);
		m_nor.emplace_back(new_normal);
		m_nor.emplace_back(new_normal);
	}
}
