#ifndef OBJLOADER_H
#define OBJLOADER_H
#include <cstdio>

bool loadOBJ(
	const char* path,
	std::vector<glm::vec3>& out_vertices,
	std::vector<glm::vec2>& out_uvs,
	std::vector<glm::vec3>& out_normals,
	std::size_t &vert_size
);

#endif