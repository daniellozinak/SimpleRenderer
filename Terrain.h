#pragma once
#include "Mesh.h"

#define VERTEX_SHADER_PATH "./VertexShader.glsl"
#define FRAGMENT_SHADER_PATH  "./FragmentShaderPhongPoint.glsl"

class Terrain : public Mesh
{
private:
	float m_amplitude = 0.9f;

	//square count per width and height (detail)
	int m_xVertices;
	int m_zVertices;

	//width and height in the world space
	int m_width;
	int m_height;
	void generatePlain();
	glm::vec3 calculateNormal(glm::vec3 currentNormal, int position);
public:
	Terrain(int xVertCount,int zVertCount,Shader *);
	Terrain(int xVertCount, int zVertCount,int width,int height, Shader*);
	Terrain(int xVertCount, int zVertCount, int width, int height,float amplitude, Shader*);

	void generateTerrain();

	inline Shader* getShader() { return m_shader; }
};

