#pragma once
#include <iostream>

#include "glad/glad.h"

#include "stb_image.h"

namespace TextureLoader
{
	unsigned int loadTexture(const char* path);
}