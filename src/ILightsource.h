#pragma once
#include "glm/glm.hpp"
class ILightsource
{
	glm::vec3 intensityCoefs;
	glm::vec3 color;
	virtual glm::vec3 getVector() = 0;
};