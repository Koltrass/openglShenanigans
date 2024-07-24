#include "TextureLoader.h"

unsigned int TextureLoader::loadTexture(const char* path)
{
	stbi_set_flip_vertically_on_load(1);
	unsigned int texture;
	glGenTextures(1, &texture);
	int texWidth, texHeight, nChannels;
	unsigned char* data = stbi_load(path, &texWidth, &texHeight, &nChannels, 0);
	if (data)
	{
		GLenum format = GL_RED;
		if (nChannels == 1)
			format = GL_RED;
		else if (nChannels == 3)
			format = GL_RGB;
		else if (nChannels == 4)
			format = GL_RGBA;
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, format, texWidth, texHeight, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}
	else
	{
		std::cout << "Failed to load texture\n";
	}
	stbi_image_free(data);
	return texture;
}
