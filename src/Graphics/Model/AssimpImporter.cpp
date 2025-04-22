#include "AssimpImporter.h"
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "Core/Image/ImageLoader.h"


AssimpImporter::AssimpImporter()
{
}

AssimpImporter::~AssimpImporter()
{
	std::cout << "[AssimpImporter] destroyed" << std::endl;
}

ModelData AssimpImporter::Import(const std::string& path)
{
	modelData = ModelData();

	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, 
								aiProcess_Triangulate | 
								aiProcess_GenSmoothNormals | 
								aiProcess_FlipUVs | 
								aiProcess_CalcTangentSpace);
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

	//std::cout << "MODELS DIRECTORY :" << directory << std::endl;

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

			//std::cout << mesh->mBitangents[i].x << std::endl;

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

	//if (scene->HasTextures()) {
	//	for (unsigned int i = 0; i < scene->mNumTextures; i++) {
	//		aiTexture* tex = scene->mTextures[i];
	//		std::cout << "Embedded texture format: " << tex->achFormatHint << std::endl;

	//		// tex->pcData に画像データが格納されてる
	//	}
	//}



	// process materials
	aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

	// diffuse maps
	std::vector<TextureData> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse", scene);
	textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

	// specular maps
	std::vector<TextureData> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular", scene);
	textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

	// normal maps
	std::vector<TextureData> normalMaps = loadMaterialTextures(material, aiTextureType_NORMALS, "texture_normal", scene);
	textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());

	// height maps
	std::vector<TextureData> heightMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_height", scene);
	textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());



	// ======== MaterialData ============
	MaterialData mat;
	mat.textures.insert(mat.textures.end(), diffuseMaps.begin(), diffuseMaps.end());
	mat.textures.insert(mat.textures.end(), specularMaps.begin(), specularMaps.end());
	mat.textures.insert(mat.textures.end(), normalMaps.begin(), normalMaps.end());
	mat.textures.insert(mat.textures.end(), heightMaps.begin(), heightMaps.end());

	int matIndex = static_cast<int>(modelData.materials.size());
	modelData.materials.push_back(mat);

	modelMesh.materialIndex = matIndex;

	return modelMesh;
}


std::vector<TextureData> AssimpImporter::loadMaterialTextures(aiMaterial* material, aiTextureType type, std::string typeName, const aiScene* scene)
{
	std::vector<TextureData> textures;


	//std::cout << "=== Material Texture Types ===" << std::endl;
	//for (int type = aiTextureType_NONE; type <= aiTextureType_UNKNOWN; ++type) {
	//	if (material->GetTextureCount((aiTextureType)type) > 0) {
	//		std::cout << "Found texture type: " << type << " (Count: "
	//			<< material->GetTextureCount((aiTextureType)type) << ")" << std::endl;
	//	}
	//}


	unsigned int count = material->GetTextureCount(type);
	for (unsigned int i = 0; i < count; i++)
	{
		aiString str;
		material->GetTexture(type, i, &str);

		std::string texPath = str.C_Str();

		bool skip = false;
		for (const auto& loaded : textures_loaded)
		{
			if (loaded.path == texPath)
			{
				textures.push_back(loaded);
				skip = true;
				break;
			}
		}
		if (skip) continue;

		TextureData texture;
		texture.type = typeName;
		texture.path = texPath;

		RawImage img;


		// [修正][修正][修正] :::(MIXAMOではうまくいかない。)::: [修正][修正][修正]
		// [修正][修正][修正] :::(MIXAMOではうまくいかない。)::: [修正][修正][修正]
		// [修正][修正][修正] :::(MIXAMOではうまくいかない。)::: [修正][修正][修正]
		// [修正][修正][修正] :::(MIXAMOではうまくいかない。)::: [修正][修正][修正]
		// 埋め込みテクスチャの場合
		if (texPath[0] == '*')
		{
			//std::cout << "[埋め込み] テクスチャ: " << texPath << std::endl;

			int index = std::stoi(texPath.substr(1));
			const aiTexture* tex = scene->mTextures[index];

			int w, h, ch;
			img.data = stbi_load_from_memory(
				reinterpret_cast<unsigned char*>(tex->pcData),
				tex->mWidth, &w, &h, &ch, 0
			);
			if (img.data)
			{
				img.width = w;
				img.height = h;
				img.channels = ch;
				img.path = texPath;
				texture.image = img;
				//std::cout << "Embedded texture loaded: " << texPath << std::endl;
			}
			else
			{
				std::cout << "Failed to load embedded texture: " << texPath << std::endl;
			}
		}
		else// 外部テクスチャの場合。(現在はUnityで埋め込みテクスチャを展開して強制的にコピーを手動でとってきている)
		{
			//std::cout << "[外部]  テクスチャ：" << texPath << std::endl;

			// [修正][修正][修正] :::もっと柔軟性を上げる必要あり::: [修正][修正][修正]
			// [修正][修正][修正] :::もっと柔軟性を上げる必要あり::: [修正][修正][修正]
			// [修正][修正][修正] :::もっと柔軟性を上げる必要あり::: [修正][修正][修正]
			// 固定パス
			std::string fileName = texPath.substr(texPath.find_last_of("/\\") + 1);
			std::string fullPath = "Assets/Textures/" + fileName;


			img = loadImageFromFile(fullPath);
			if (img.data)
			{
				texture.image = img;
				//std::cout << "External texture loaded: " << fullPath << std::endl;
			}
			else
			{
				std::cout << "Failed to load external texture: " << fullPath << std::endl;
				continue;
			}
		}

		textures.push_back(texture);
		textures_loaded.push_back(texture);
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