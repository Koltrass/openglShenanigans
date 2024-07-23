#pragma once
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "assimp/config.h"
#include "assimp/revision.h"

#include "Mesh.h"
#include "TextureLoader.h"

class Model
{
public:
	Model(std::string path);

	void Draw(Shader& shader);
private:
	std::vector<Texture> texturesLoaded;
	std::vector<Mesh> meshes;
	std::string directory;

	void loadModel(std::string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial* material,
		aiTextureType type, TextureType endType);
};