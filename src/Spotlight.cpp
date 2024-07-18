#include "Spotlight.h"
Spotlight::Spotlight(glm::vec3 color, glm::vec3 position, glm::vec3 direction,
	glm::vec3 intensityCoefs, float innerCutoff, float outerCutoff) :
	ILightsource(color), position(position), direction(direction),
	intensityCoefs(intensityCoefs), innerCutoff(innerCutoff),
	outerCutoff(outerCutoff) {}

glm::vec3 Spotlight::getDirectionVector(glm::vec3 viewPosition)
{
	return glm::vec3(position - viewPosition);
}
