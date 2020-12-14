#pragma once
#include "Curve.h"
#include "glm/mat4x4.hpp"
#include <vector>

#define COUNT 4
class BezierCurve : public Curve
{
private:
	glm::vec3 m_points[COUNT];
	glm::mat4 m_matrix;

	float m_data[16] = {
	   -1,  3, -3,  1,
	    3, -6,  3,  0,
	   -3,  3,  0,  0,
	    1,  0,  0,  0
	};
public:
	BezierCurve(std::vector<glm::vec3>);
	glm::vec3 getCurrentPoint(float t) override;
};

