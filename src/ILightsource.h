#pragma once
#include "glm/glm.hpp"
struct ILightsource
{
public:
	glm::vec3 color;

	ILightsource(glm::vec3 color);
	virtual glm::vec3 getDirectionVector(glm::vec3 viewPosition) = 0;
};