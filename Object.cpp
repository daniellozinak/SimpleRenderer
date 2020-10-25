#include "Object.h"


//GLuint Object::m_VAO;
bool Object::m_isVAOinit = false;

Object::Object()
{
	this->m_modelMatrix = glm::mat4(1.0f);
	this->m_init();
}

Object::Object(std::vector<util::Vertex> vert, std::size_t numberOfVert)
{
	this->m_initVert(vert, numberOfVert);
	this->m_init();
	this->m_modelMatrix = glm::mat4(1.0f);
}

Object::Object(std::vector<util::Vertex> vert, std::size_t numberOfVert, glm::mat4 modelMatrix)
{
	this->m_initVert(vert, numberOfVert);
	this->m_modelMatrix = modelMatrix;
	this->m_init();
}

void Object::move(glm::vec3 vec)
{
	this->m_modelMatrix = glm::translate(this->m_modelMatrix, vec);
}


void Object::m_initVert(std::vector<util::Vertex> vert, std::size_t numberOfVert) {
	for (std::size_t i = 0; i < numberOfVert; i++) {
		this->m_pos.push_back(vert[i].position);
		this->m_col.push_back(vert[i].color);
	}

	this->m_numberOfVert = numberOfVert;
}

void Object::setShader(Shader*shader)
{
	this->m_shader = shader;
}

void Object::draw()
{
	glBindVertexArray(m_VAO);
	this->m_shader->bind();
	this->m_shader->sendUniform("modelMatrix", this->m_modelMatrix);
	glDrawArrays(GL_TRIANGLES, 0,m_numberOfVert);
}

void Object::rotate()
{
	this->m_modelMatrix = glm::rotate(this->m_modelMatrix, 0.01f, glm::vec3(1.0f, 0.0f, 0.0f));
}

void Object::rotateAroundAxis(float a1, float a2) {
	this->m_modelMatrix = glm::rotate(this->m_modelMatrix, -a1, glm::vec3(1.0f, 0.0f, 0.0f));
	this->m_modelMatrix = glm::rotate(this->m_modelMatrix, -a2, glm::vec3(0.0f, 0.0f, 1.0f));
	this->m_modelMatrix = glm::rotate(this->m_modelMatrix, 0.02f, glm::vec3(0.0f, 1.0f, 0.0f));
	this->m_modelMatrix = glm::rotate(this->m_modelMatrix, a2, glm::vec3(0.0f, 0.0f, 1.0f));
	this->m_modelMatrix = glm::rotate(this->m_modelMatrix, a1, glm::vec3(1.0f, 0.0f, 0.0f));

}

void Object::m_init() {

	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);
	Object::m_isVAOinit = true;


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

std::size_t Object::getCount() { return this->m_numberOfVert; }

GLuint Object::getVAO() { return this->m_VAO; }

glm::mat4 Object::getModelMatrix() { return this->m_modelMatrix; }



Object::~Object()
{
}