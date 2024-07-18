#pragma once
#include "ILightsource.h"
struct DirectionLight : public ILightsource
{
public:
	glm::vec3 direction;

	DirectionLight(glm::vec3 color, glm::vec3 direction);
	virtual glm::vec3 getDirectionVector(glm::vec3 viewPosition) override;
};

