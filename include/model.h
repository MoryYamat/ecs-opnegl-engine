#pragma once
#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <string>
#include <fstream>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

#include "Mesh.h"
#include "Shader.h"

class Model {
public:
	// テクスチャデータ
	std::vector<Texture> textures_loaded;

	// メッシュデータ
	std::vector<Mesh> meshes;

	std::string  directory;
	bool gammaCorrection;
	
	// 将来的には、gammaCorrection を使いたい...
	Model(std::string const&filepath, bool gamma = false);

	// Draw
	void Draw(Shader& shader);

private:
	void loadModel(std::string const& filepath);

	void processNode(aiNode* node, const aiScene* scene);

	Mesh processMesh(aiMesh* mesh, const aiScene* scene);

	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);

	unsigned int TextureFromFile(const char* filepath, const std::string& directory, bool gamma=false);
};