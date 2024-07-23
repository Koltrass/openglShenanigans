#pragma once
#include <vector>

#include "glad/glad.h"

#include "Vertex.h"
#include "Texture.h"
#include "Shader.h"
class Mesh
{
public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;
	
	Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices,
		std::vector<Texture>& textures);
	void Draw(Shader& shader);
private:
	unsigned int VAO, VBO, EBO;
	void setupMesh();
};