#include "Mesh.h"



Mesh::Mesh(std::vector<util::Vertex> vert, std::size_t numberOfVert)
{
	this->m_initVert(vert, numberOfVert);
	this->m_init();
}

void Mesh::bind()
{
	glBindVertexArray(m_VAO);
}

void Mesh::m_initVert(std::vector<util::Vertex> vert, std::size_t numberOfVert) {
	for (std::size_t i = 0; i < numberOfVert; i++) {
		this->m_pos.push_back(vert[i].position);
		this->m_col.push_back(vert[i].color);
	}

	this->m_numberOfVert = numberOfVert;
}

void Mesh::m_init() {

	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	//VBO position
	glGenBuffers(1, &this->m_VBOPos);
	glBindBuffer(GL_ARRAY_BUFFER, this->m_VBOPos);
	glBufferData(GL_ARRAY_BUFFER, this->m_pos.size() * sizeof(glm::vec3), this->m_pos.data(), GL_STATIC_DRAW);

	//enable vertex attribute for position on layout=0
	glEnableVertexAttribArray(GL_POSITION_LAYOUT);
	glBindBuffer(GL_ARRAY_BUFFER, this->m_VBOPos);
	glVertexAttribPointer(
		GL_POSITION_LAYOUT,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
	);

	//VBO color
	glGenBuffers(1, &this->m_VBOCol);
	glBindBuffer(GL_ARRAY_BUFFER, this->m_VBOCol);
	glBufferData(GL_ARRAY_BUFFER, this->m_col.size() * sizeof(glm::vec3), this->m_col.data(), GL_STATIC_DRAW);

	//enable vertex attribute for color on layout=1
	glEnableVertexAttribArray(GL_COLOR_LAYOUT);
	glBindBuffer(GL_ARRAY_BUFFER, this->m_VBOCol);
	glVertexAttribPointer(
		GL_COLOR_LAYOUT,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
	);
}