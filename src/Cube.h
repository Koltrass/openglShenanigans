#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Material.h"

struct Cube
{
	glm::vec3 location;
	float scaling;
	Material material;
};