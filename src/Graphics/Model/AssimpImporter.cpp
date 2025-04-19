#include "AssimpImporter.h"
#include <iostream>
#include <stb_image.h>

#include "Core/Image/ImageLoader.h"


AssimpImporter::AssimpImporter()
{
}

ModelData AssimpImporter::Import(const std::string& path)
{
	modelData = ModelData();

	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
	// エラー処理(error handling)
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
		//読み込み失敗フラグ(もし必要なら...)
		//modelData.isValid = false;
		return modelData;
	}
	else
	{
		std::cout << "LOAD COMPELETED!" << std::endl;
	}

	directory = path.substr(0, path.find_last_of('/'));

	processNode(scene->mRootNode, scene);


	//所有権が移譲(まじかよ)
	return modelData;
}

//void AssimpImporter::Import(const std::string& path)
//{
//	Assimp::Importer importer;
//	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
//	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
//	{
//		std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
//		return;
//	}
//	else
//	{
//		std::cout << "ASSIMP MODEL LOAD COMPELETED!" << std::endl;
//	}
//
//	ModelData modelData;
//
//	processNode(scene->mRootNode, scene, modelData);
//
//
//
//	//return model;
//}

void AssimpImporter::processNode(aiNode* node, const aiScene* scene) 
{
	//std::cout << "Node " << node->mName.C_Str() << 
	//		", NumMeshes: " << node->mNumMeshes <<
	//		", Children:  " << node->mNumChildren << std::endl;

	for (unsigned int i = 0; i < node->mNumMeshes; i++) 
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];

		modelData.meshes.push_back(processMesh(mesh, scene));


	}

	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		// 再帰
		processNode(node->mChildren[i], scene);
	}
}

MeshData AssimpImporter::processMesh(aiMesh* mesh, const aiScene* scene)
{
	glm::vec3 vector;
	Vertex vertex;

	std::vector<TextureData> textures;

	MeshData modelMesh;

	for (unsigned int i = 0; i < mesh->mNumVertices; i++) 
	{
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.position = vector;

		//std::cout << "postion data x: " << vector.x << std::endl;

		if (mesh->HasNormals()) 
		{
			vector.x = mesh->mNormals[i].x;
			vector.y = mesh->mNormals[i].z;
			vector.z = mesh->mNormals[i].z;
			vertex.normal = vector;
		}

		if (mesh->mTextureCoords[0])
		{
			glm::vec2 vec;


			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.texCoords = vec;

			//tangent
			vector.x = mesh->mTangents[i].x;
			vector.y = mesh->mTangents[i].y;
			vector.z = mesh->mTangents[i].z;
			vertex.tangent = vector;

			//bitangent
			vector.x = mesh->mBitangents[i].x;
			vector.y = mesh->mBitangents[i].y;
			vector.z = mesh->mBitangents[i].z;
			vertex.bitangent = vector;

			//std::cout << "vertex info num: " << i << "times" <<  std::endl;
		}
		else {
			vertex.texCoords = glm::vec2(0.0f);
		}
		modelMesh.vertices.push_back(vertex);
	}

	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];

		//std::cout << "Triangle: " << i << "uses vertices: ";

		for (unsigned int j = 0; j < face.mNumIndices ; j++)
		{
			modelMesh.indices.push_back(face.mIndices[j]);
			//std::cout << face.mIndices[j] << " ";
		}

		//std::cout << std::endl;
	}

	// process materials
	aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

	// diffuse maps
	std::vector<TextureData> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
	textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

	// specular maps
	std::vector<TextureData> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
	textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

	// normal maps
	std::vector<TextureData> normalMaps = loadMaterialTextures(material, aiTextureType_NORMALS, "texture_normal");
	textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());

	// height maps
	std::vector<TextureData> heightMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_height");
	textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

	return modelMesh;
}


std::vector<TextureData> AssimpImporter::loadMaterialTextures(aiMaterial* material, aiTextureType type, std::string typeName)
{
	std::vector<TextureData> textures;

	for (unsigned int i = 0; i < material->GetTextureCount(type); i++) 
	{
		aiString str;
		// get texture's path
		material->GetTexture(type, i, &str);

		std::string fullpath = this->directory + "/" + std::string(str.C_Str());

		bool skip = false;
		for (unsigned int j = 0; j < textures_loaded.size(); j++)
		{
			if (textures_loaded[j].path == str.C_Str()) {
				textures.push_back(textures_loaded[j]);
				skip = true;
				break;
			}

			if (!skip)
			{
				TextureData texture;
				texture.type = typeName;
				texture.path = str.C_Str();
				texture.image = loadImageFromFile(fullpath);  // ← ここでRawImage構造体に読み込む

				textures.push_back(texture);
				textures_loaded.push_back(texture);

				std::cout << "Loaded texture [" << typeName << "] at " << texture.path << std::endl;
			}

		}



	}

	return textures;
}



//将来的なエラーハンドリングのためのフラグの候補
//template <typename T>
//struct ImportResult {
//	T data;
//	bool success = true;
//	std::string errorMessage;
//};