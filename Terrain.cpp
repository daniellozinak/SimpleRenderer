#include "Terrain.h"
#include "glm/gtc/noise.hpp"
#include "glm/gtx/string_cast.hpp"
#include <vector>

Terrain::Terrain(int xVertCount, int zVertCount) : Mesh(new Shader(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH))
{
	m_width = 5;
	m_height = 5;
	m_xVertices = xVertCount;
	m_zVertices = zVertCount;
	generateTerrain();
	m_init();
}

Terrain::Terrain(int xVertCount, int zVertCount, int width, int height) : Mesh(new Shader(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH))
{
	m_width = width;
	m_height = height;
	m_xVertices = xVertCount;
	m_zVertices = zVertCount;
	generateTerrain();
	m_init();
}

Terrain::Terrain(int xVertCount, int zVertCount, int width, int height, float amplitude) : Mesh(new Shader(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH))
{
	m_width = width;
	m_height = height;
	m_xVertices = xVertCount;
	m_zVertices = zVertCount;
	m_amplitude = amplitude;
	generateTerrain();
	m_init();
}

void Terrain::generatePlain()
{
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
	float max = m_pos.at(0).y;
	float min = m_pos.at(0).y;
	for (int i = 0; i < m_numberOfVert; i++)
	{
		glm::vec2 vertex_xz = glm::vec2(m_pos.at(i).x, m_pos.at(i).z);
		float new_y = m_amplitude * glm::perlin(vertex_xz);

		m_pos.at(i) = glm::vec3(m_pos.at(i).x, new_y, m_pos.at(i).z);

		if (m_pos.at(i).y > max)
		{
			max = m_pos.at(i).y;
		}

		if (m_pos.at(i).y < min)
		{
			min = m_pos.at(i).y;
		}

		//std::cout << glm::to_string(m_pos.at(i)) << std::endl;

	}

	std::cout << "MAX HEIGHT: " << m_amplitude * max << std::endl;
	std::cout << "MIN HEIGHT: " << m_amplitude * min << std::endl;

	this->m_shader->sendUniform("max_height", m_amplitude * max);

	//gen normals
	for (int i = 0; i < m_numberOfVert; i +=3)
	{
		glm::vec3 vector1 = m_pos.at(i + 1) - m_pos.at(i);
		glm::vec3 vector2 = m_pos.at(i + 2) - m_pos.at(i);
		glm::vec3 new_normal = glm::cross(vector1, vector2);


		m_nor.emplace_back(new_normal);
		m_nor.emplace_back(new_normal);
		m_nor.emplace_back(new_normal);
	}


	for (int i = 0; i < m_nor.size(); i++)
	{
		m_nor.at(i) = calculateNormal(m_nor.at(i), i);

	}
}

glm::vec3 Terrain::calculateNormal(glm::vec3 currentNormal, int position)
{
	float neighbourWight = 8.0f;
	int normalCount = m_nor.size();
	if (position - 1 < 0 || position - m_zVertices < 0 || position + 1 >= normalCount || position + m_zVertices >= normalCount)
	{
		return currentNormal;
	}
	int pos0 = position - m_zVertices;
	int pos1 = position + 1;
	int pos2 = position + m_zVertices;
	int pos3 = position - 1;


	glm::vec3 neighbourNormal0 = m_nor.at(position - m_zVertices) * neighbourWight;
	glm::vec3 neighbourNormal1 = m_nor.at(position + 1) * neighbourWight;
	glm::vec3 neighbourNormal2 = m_nor.at(position + m_zVertices) * neighbourWight;
	glm::vec3 neighbourNormal3 = m_nor.at(position - 1) * neighbourWight;


	return (neighbourNormal0 + neighbourNormal1 + neighbourNormal2 + neighbourNormal3 + (currentNormal)*16.0f) / 5.0f;
}
