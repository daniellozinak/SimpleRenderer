#include "Mesh.h"
#include "SOIL.h"
#include "object_loader.hpp"

int Mesh::idGenerator = 1;

Mesh::Mesh(std::vector<util::Vertex> vert, std::size_t numberOfVert,Shader *shader)
{
	this->m_initVert(vert, numberOfVert);
	this->m_shader = shader;
	this->m_init();
	this->generateID();
}

Mesh::Mesh(const char* modelPath,Shader *shader)
{

	if (!loadOBJ(modelPath, m_pos, m_tex, m_nor, m_numberOfVert))
	{
		std::cout << "Cant load object" << std::endl;
		exit(1);
	}
	this->m_shader = shader;
	this->m_init();
	this->generateID();
}


Mesh::Mesh(Shader* shader)
{
	this->m_shader = shader;
	this->generateID();
}


bool Mesh::loadFromObj(const char* filePath)
{
	return loadOBJ(filePath, m_pos, m_tex, m_nor, m_numberOfVert);
}

void Mesh::bind()
{
	glBindVertexArray(m_VAO);
	this->m_shader->bind();

	if (m_texture != nullptr)
	{
		m_texture->bind();
		int toSend = m_texture->getTextureUnit();
		this->m_shader->sendUniform("textureUnitID", toSend);
	}
	
}

void Mesh::unbind()
{
	this->m_shader->unbind();
	glBindVertexArray(0);

	if (m_texture != nullptr){ m_texture->unbind(); }
}

void Mesh::operation()
{
	this->bind();
}

void Mesh::updateModel(glm::mat4& model)
{
	this->m_shader->sendUniform("modelMatrix", model);

	//highlight mesh if selected (color multiplied by 3)
	if (is_selected)
	{
		this->m_shader->sendUniform(SHADER_SELECT_LOCATION, 3);
	}
	else {
		this->m_shader->sendUniform(SHADER_SELECT_LOCATION, 1);
	}	
}

void Mesh::m_initVert(std::vector<util::Vertex> vert, std::size_t numberOfVert) {
	for (std::size_t i = 0; i < numberOfVert; i++) {
		this->m_pos.push_back(vert[i].position);
		this->m_nor.push_back(vert[i].color);
		this->m_tex.push_back(vert[i].texture);
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

	//VBO normal
	glGenBuffers(1, &this->m_VBONor);
	glBindBuffer(GL_ARRAY_BUFFER, this->m_VBONor);
	glBufferData(GL_ARRAY_BUFFER, this->m_nor.size() * sizeof(glm::vec3), this->m_nor.data(), GL_STATIC_DRAW);

	//enable vertex attribute for normal on layout=1
	glEnableVertexAttribArray(GL_NORMAL_LAYOUT);
	glBindBuffer(GL_ARRAY_BUFFER, this->m_VBONor);
	glVertexAttribPointer(
		GL_NORMAL_LAYOUT,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
	);


	//VBO texture
	glGenBuffers(1, &this->m_VBOTex);
	glBindBuffer(GL_ARRAY_BUFFER, this->m_VBOTex);
	glBufferData(GL_ARRAY_BUFFER, this->m_tex.size() * sizeof(glm::vec2), this->m_tex.data(), GL_STATIC_DRAW);

	//enable vertex attribute for texture on layout=2
	glEnableVertexAttribArray(GL_TEXTURE_LAYOUT);
	glBindBuffer(GL_ARRAY_BUFFER, this->m_VBOTex);
	glVertexAttribPointer(
		GL_TEXTURE_LAYOUT,
		2,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
	);
}

bool Mesh::addTexture(Texture* texture)
{
	m_texture = texture;
	m_texture->bind();
	int toSend = texture->getTextureUnit();
	this->m_shader->sendUniform("textureUnitID", toSend);
	
	return true;
}

void Mesh::generateID()
{
	this->m_ID = idGenerator;
	idGenerator++;
}
Mesh* Mesh::clone()
{
	return new Mesh(*this);
}