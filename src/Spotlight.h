#pragma once
#include "ILightsource.h"
class Spotlight : public ILightsource
{
	glm::vec3 position;
	glm::vec3 direction;
	float innerCutoff;
	float outerCutoff;
	virtual glm::vec3 getVector() override;
};

