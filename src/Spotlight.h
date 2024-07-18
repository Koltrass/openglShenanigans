#pragma once
#include "ILightsource.h"
struct Spotlight : public ILightsource
{
public:
	glm::vec3 position;
	glm::vec3 direction;
	glm::vec3 intensityCoefs;

	float innerCutoff;
	float outerCutoff;

	Spotlight(glm::vec3 color, glm::vec3 position, glm::vec3 direction,
		glm::vec3 intensityCoefs, float innerCutoff, float outerCutoff);

	virtual glm::vec3 getDirectionVector(glm::vec3 viewPosition) override;
};

