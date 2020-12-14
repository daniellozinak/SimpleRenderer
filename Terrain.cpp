#include "Terrain.h"
#include "glm/gtc/noise.hpp"
#include "glm/gtx/string_cast.hpp"
#include <vector>

Terrain::Terrain(int xVertCount, int zVertCount, Shader*shader) : Mesh(shader)
{
	m_width = 5;
	m_height = 5;
	m_xVertices = xVertCount;
	m_zVertices = zVertCount;
	generateTerrain();
	m_init();
}

Terrain::Terrain(int xVertCount, int zVertCount, int width, int height, Shader*shader) : Mesh(shader)
{
	m_width = width;
	m_height = height;
	m_xVertices = xVertCount;
	m_zVertices = zVertCount;
	generateTerrain();
	m_init();
}

Terrain::Terrain(int xVertCount, int zVertCount, int width, int height, float amplitude, Shader* shader) : Mesh(shader)
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
	for (int i = 0; i < m_numberOfVert; i++)
	{
		glm::vec2 vertex_xz = glm::vec2(m_pos.at(i).x, m_pos.at(i).z);
		float new_y = m_amplitude * glm::perlin(vertex_xz);

		m_pos.at(i) = glm::vec3(m_pos.at(i).x, new_y, m_pos.at(i).z);

		if (m_pos.at(i).y > max)
		{
			max = m_pos.at(i).y;
		}
	}

	this->m_shader->sendUniform("max_height", m_amplitude * max);

	////gen normals
	for (int i = 0; i < m_numberOfVert; i +=3)
	{
		glm::vec3 vector1 = m_pos.at(i + 1) - m_pos.at(i);
		glm::vec3 vector2 = m_pos.at(i + 2) - m_pos.at(i);
		glm::vec3 new_normal = glm::cross(vector1, vector2);

		m_nor.emplace_back(-1.0f * new_normal);
		m_nor.emplace_back(-1.0f * new_normal);
		m_nor.emplace_back(-1.0f * new_normal);
	}

	for (int i = 0; i < m_nor.size(); i++)
	{
		glm::vec3 original = m_nor.at(i);
		glm::vec3 changed = calculateNormal(m_nor.at(i), i);
		m_nor[i] = changed;
	}
}

glm::vec3 Terrain::calculateNormal(glm::vec3 currentNormal, int position)
{
	glm::vec3 normal0 = currentNormal;
	glm::vec3 normal1 = currentNormal;
	glm::vec3 normal2 = currentNormal;
	glm::vec3 normal3 = currentNormal;
	glm::vec3 normal4 = currentNormal;
	glm::vec3 normal5 = currentNormal;

	std::size_t count = m_nor.size();


	int pos1 = position - 1;
	normal1 = (pos1 >= 0) ? m_nor[pos1] : currentNormal;

	int pos2 = position - 1 - 3;
	normal2 = (pos2 >= 0) ? m_nor[pos2] : currentNormal;

	int pos3 = position - (1 - (-1*(3 * m_zVertices)));
	normal3 = (pos3 >=0) ? m_nor[pos3] : currentNormal;

	int pos4 = position - (1 - (- 1 * (3 * (m_zVertices + 1))));
	normal4 = (pos4 >= 0) ? m_nor[pos4] : currentNormal;

	int pos5 = position - (1 - (- 1 * (3 * (m_zVertices + 2))));
	normal5 = (pos5 >= 0) ? m_nor[pos5] : currentNormal;


	
	//int pos1 = position + 2;
	//normal1 = (pos1 < count) ? m_nor[pos1] : currentNormal;

	//int pos2 = position + 2 + 3;
	//normal2 = (pos2 < count) ? m_nor[pos2] : currentNormal;

	//int pos3 = position - ((3 * (m_zVertices - 1)));
	//normal3 = (pos3 >= 0) ? m_nor[pos3] : currentNormal;

	//int pos4 = position - ((3 * (m_zVertices)));
	//normal4 = (pos4 >= 0) ? m_nor[pos4] : currentNormal;

	//int pos5 = position - ((3 * (m_zVertices + 1)));
	//normal5 = (pos5 >= 0) ? m_nor[pos5] : currentNormal;
	

	
	
	/*int pos1 = position + 1;
	normal1 = (pos1 < count) ? m_nor[pos1] : currentNormal;

	int pos2 = position - 3;
	normal2 = (pos2 >= 0) ? m_nor[pos2] : currentNormal;

	int pos3 = position + 1 + ((3 * (m_zVertices - 1)));
	normal3 = (pos3 < count) ? m_nor[pos3] : currentNormal;

	int pos4 = position + 1 + ((3 * (m_zVertices)));
	normal4 = (pos4 < count) ? m_nor[pos4] : currentNormal;

	int pos5 = position + 1 + ((3 * (m_zVertices + 1)));
	normal5 = (pos5 < count) ? m_nor[pos5] : currentNormal;*/
	

	return (normal0 + normal1 + normal2  + normal3  + normal4 + normal5 ) / 6.0f;
}
