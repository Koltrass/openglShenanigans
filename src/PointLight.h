#pragma once
#include "ILightsource.h"
struct PointLight : public ILightsource
{
public:
	glm::vec3 position;
	glm::vec3 intensityCoefs;

	PointLight(glm::vec3 color, glm::vec3 position, glm::vec3 intensityCoefs);

	virtual glm::vec3 getDirectionVector(glm::vec3 viewPosition) override;
};
