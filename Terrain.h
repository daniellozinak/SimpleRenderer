#pragma once
#include "Mesh.h"

class Terrain : public Mesh
{
private:
	float m_altitude = 0.9f;
	int m_xVertices;
	int m_zVertices;
	int m_width;
	int m_height;

	void generatePlain();
public:
	Terrain(Shader*,int xVertCount,int zVertCount);

	void generateTerrain();
};

