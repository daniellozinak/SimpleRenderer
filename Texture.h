#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h> 

class Texture
{
	private:
		GLuint m_id;
		GLenum m_type;
		int m_textureUnit;
	public:
		Texture(GLenum type, GLuint textureUnit);
		~Texture();

		void bind();
		void unbind();

		inline GLuint getId() { return m_id; }
		inline GLuint getType() { return m_type; }
		inline GLuint getTextureUnit() { return m_textureUnit; }

		inline void setId(GLuint id) { m_id = id; }
		inline void setType(GLenum type) { m_type = type; }
};

