#pragma once

#include <GLM/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

#include "ImageData.h"

#define MAX_BONE_INFLUENCE 4


// 個別のテクスチャ
struct TextureData {
	std::string type;
	std::string path;
	RawImage image;// 実体...
};

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoords;
	glm::vec3 tangent;
	glm::vec3 bitangent;

	int boneIDs[MAX_BONE_INFLUENCE];
	float weights[MAX_BONE_INFLUENCE];
};

// meshdata(VAOなど描画に必要な情報を含む)
struct MeshData {
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	int textureIndex; // index into ModelData::textures
};

// モデルデータ: 複数のメッシュとその関連テクスチャ群
struct ModelData {
	std::vector<MeshData> meshes;
	std::vector<TextureData> textures;

	//ロード成否フラグ
	bool isValid = true;
};


//====================================================
//ModelData
//├── MeshData[]
//│   ├── Vertex[]
//│   │   ├── glm::vec3 position
//│   │   ├── glm::vec3 normal
//│   │   ├── glm::vec2 texCoords
//│   │   └── ...（bone情報など）
//│   └── std::vector<unsigned int> indices
//│
//└── TextureData[]
//├── unsigned int id
//├── std::string type
//└── std::string path
//====================================================