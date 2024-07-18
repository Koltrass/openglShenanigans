#include "PointLight.h"

PointLight::PointLight(glm::vec3 color, glm::vec3 position, glm::vec3 intensityCoefs) :
    ILightsource(color), position(position), intensityCoefs(intensityCoefs) {}

glm::vec3 PointLight::getDirectionVector(glm::vec3 viewPosition)
{
    return glm::vec3(this->position - viewPosition);
}
