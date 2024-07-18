#include "DirectionLight.h"

DirectionLight::DirectionLight(glm::vec3 color, glm::vec3 direction) :
    ILightsource(color), direction(direction) {}

glm::vec3 DirectionLight::getDirectionVector(glm::vec3 viewPosition)
{
    return -direction;
}
