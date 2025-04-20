#pragma once
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "ModelData.h"

// factory
class AssimpImporter {
public:
	


	// 将来的には、gammaCorrection を使いたい...
	AssimpImporter();

	ModelData Import(std::string const& path);


	//const std::vector<MeshData> getMeshes() const { return meshes; }

private:
	ModelData modelData;

	// テクスチャデータ
	std::vector<TextureData> textures_loaded;
	// メッシュデータ
	std::string  directory;
	bool gammaCorrection;


	void processNode(aiNode* node, const aiScene* scene);

	MeshData processMesh(aiMesh* mesh, const aiScene* scene);

	std::vector<TextureData> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName, const aiScene* scene);

	//unsigned int textureFromFile(const char* path, const std::string& directory, bool gamma = false);

};