#include "data_loader.hpp"
#include "data.h"

std::vector<util::Vertex> loadSphere()
{
	std::vector<util::Vertex> toReturn;
	for (int i = 0; i < sphere; i++)
	{
		VertexNoTex vData = VERTICES[i];
		glm::vec3 tempPos = { vData.Position[0],vData.Position[1],vData.Position[2] };
		glm::vec3 tempNormal = { vData.Normal[0],vData.Normal[1],vData.Normal[2] };
		util::Vertex tempVert = { tempPos,tempNormal };
		toReturn.push_back(tempVert);
	}
	return toReturn;
}

std::vector<util::Vertex> loadPlain()
{
	std::vector<util::Vertex> toReturn;
	for (int i = 0; i < plain; i++)
	{
		VertexData vData = vertices_plain[i];
		glm::vec3 tempPos = { vData.Position[0],vData.Position[1],vData.Position[2] };
		glm::vec3 tempNormal = { vData.Normal[0],vData.Normal[1],vData.Normal[2] };
		glm::vec2 tempTexture = { vData.Texture[0],vData.Texture[1] };
		util::Vertex tempVert = { tempPos,tempNormal,tempTexture };
		toReturn.push_back(tempVert);
	}
	return toReturn;
}