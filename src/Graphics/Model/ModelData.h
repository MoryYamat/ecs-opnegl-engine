#pragma once

#include <GLM/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

#include "ImageData.h"

#define MAX_BONE_INFLUENCE 4


// �ʂ̃e�N�X�`��
struct TextureData {
	std::string type;
	std::string path;
	RawImage image;// ����...
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

// meshdata(VAO�ȂǕ`��ɕK�v�ȏ����܂�)
struct MeshData {
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	int textureIndex; // index into ModelData::textures
};

// ���f���f�[�^: �����̃��b�V���Ƃ��̊֘A�e�N�X�`���Q
struct ModelData {
	std::vector<MeshData> meshes;
	std::vector<TextureData> textures;

	//���[�h���ۃt���O
	bool isValid = true;
};


//====================================================
//ModelData
//������ MeshData[]
//��   ������ Vertex[]
//��   ��   ������ glm::vec3 position
//��   ��   ������ glm::vec3 normal
//��   ��   ������ glm::vec2 texCoords
//��   ��   ������ ...�ibone���Ȃǁj
//��   ������ std::vector<unsigned int> indices
//��
//������ TextureData[]
//������ unsigned int id
//������ std::string type
//������ std::string path
//====================================================