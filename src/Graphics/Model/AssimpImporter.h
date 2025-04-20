#pragma once
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "ModelData.h"

// factory
class AssimpImporter {
public:
	


	// �����I�ɂ́AgammaCorrection ���g������...
	AssimpImporter();

	ModelData Import(std::string const& path);


	//const std::vector<MeshData> getMeshes() const { return meshes; }

private:
	ModelData modelData;

	// �e�N�X�`���f�[�^
	std::vector<TextureData> textures_loaded;
	// ���b�V���f�[�^
	std::string  directory;
	bool gammaCorrection;


	void processNode(aiNode* node, const aiScene* scene);

	MeshData processMesh(aiMesh* mesh, const aiScene* scene);

	std::vector<TextureData> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName, const aiScene* scene);

	//unsigned int textureFromFile(const char* path, const std::string& directory, bool gamma = false);

};