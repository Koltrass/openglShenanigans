#pragma once
#include <string>
enum TextureType
{
	DIFFUSE,
	SPECULAR
};
struct Texture
{
	unsigned int id;
	TextureType type;
};