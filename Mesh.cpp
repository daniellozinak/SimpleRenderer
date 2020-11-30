#include "Mesh.h"
#include "SOIL.h"
#include "object_loader.hpp"

GLint Mesh::idGenerator = 1;
int Mesh::offset = 0;

Mesh::Mesh(std::vector<util::Vertex> vert, std::size_t numberOfVert,Shader *shader)
{
	this->m_initVert(vert, numberOfVert);
	this->m_shader = shader;

	this->m_ID = idGenerator;
	idGenerator++;
	this->m_init();
}

Mesh::Mesh(const char* modelPath,Shader *shader)
{

	if (!loadOBJ(modelPath, m_pos, m_tex, m_nor, m_numberOfVert))
	{
		std::cout << "Cant load object" << std::endl;
		exit(1);
	}
	this->m_shader = shader;

	this->m_ID = idGenerator;
	idGenerator++;
	this->m_init();

	std::cout << "size: " << m_numberOfVert << std::endl;
	
}

void Mesh::bind()
{
	glBindVertexArray(m_VAO);
	this->m_shader->bind();
}

void Mesh::unbind()
{
	this->m_shader->unbind();
	glBindVertexArray(0);
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

bool Mesh::addTexture(const char* path)
{
	glActiveTexture(GL_TEXTURE0 + offset);

	this->m_TextureID = SOIL_load_OGL_texture(path, SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	if (m_TextureID == 0)
	{
		std::cout << "[SOIL Error] Texture loading failed Message: [" << SOIL_last_result() << "]\n";
		return false;
	}
	std::cout << "Texture successfully loaded: " << this->m_TextureID << "\n";
	offset += 1;

	glBindTexture(GL_TEXTURE_2D, this->m_TextureID);

	this->m_shader->sendUniform("textureUnitID", (float)this->m_TextureID);

	return true;
}


