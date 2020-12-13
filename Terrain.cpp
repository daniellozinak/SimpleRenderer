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

	}

	std::cout << "MAX HEIGHT: " << m_amplitude * max << std::endl;
	std::cout << "MIN HEIGHT: " << m_amplitude * min << std::endl;

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


	int count = 0;
	for (int i = 0; i < m_nor.size(); i++)
	{
		glm::vec3 original = m_nor.at(i);
		glm::vec3 changed = calculateNormal(m_nor.at(i), i);
		count += (changed != original) ? 1 : 0;
		//m_nor[i] = changed;
	}

	std::cout << "COUNT: " << count << " / " << m_nor.size() << std::endl;
}

glm::vec3 Terrain::calculateNormal(glm::vec3 currentNormal, int position)
{

	glm::vec3 neighbourNormal0 = currentNormal;
	glm::vec3 neighbourNormal1 = currentNormal;
	glm::vec3 neighbourNormal2 = currentNormal;
	glm::vec3 neighbourNormal3 = currentNormal;

	glm::vec3 cornerNormal0 = currentNormal;
	glm::vec3 cornerNormal1 = currentNormal;
	glm::vec3 cornerNormal2 = currentNormal;
	glm::vec3 cornerNormal3 = currentNormal;


	float neighbourWeight = 0.05f;
	float cornerWeight = 0.01f;
	float currentWeight = 1.0f;
	int normalCount = m_nor.size();


	int pos0 = position - m_zVertices;
	int pos1 = position + 1;
	int pos2 = position + m_zVertices;
	int pos3 = position - 1;

	int corner0 = position + m_zVertices - 1;
	int corner1 = position - m_zVertices - 1;
	int corner2 = position + m_zVertices + 1;
	int corner3 = position - m_zVertices + 1;

	if (pos0 >= 0) { neighbourNormal0 = m_nor.at(pos0) * neighbourWeight; }
	if(pos1 < normalCount) { neighbourNormal1 = m_nor.at(pos1) * neighbourWeight; }
	if(pos2 < normalCount) {  neighbourNormal2 = m_nor.at(pos2) * neighbourWeight; }
	if(pos3 >=0) {  neighbourNormal3 = m_nor.at(pos3) * neighbourWeight; }

	if (corner0 < normalCount) { cornerNormal0 = m_nor.at(corner0) * cornerWeight; }
	if (corner1 >= 0) { cornerNormal1 = m_nor.at(corner1) * cornerWeight; }
	if (corner2 < normalCount) { cornerNormal2 = m_nor.at(corner2) * cornerWeight; }
	if (corner3 >= 0) { cornerNormal3 = m_nor.at(corner3) * cornerWeight; }

	return (neighbourNormal0 + neighbourNormal1 + neighbourNormal2 + neighbourNormal3 + cornerNormal0 + cornerNormal1 + cornerNormal2 + cornerNormal3 + (currentNormal * currentWeight)) / 9.0f;
}
