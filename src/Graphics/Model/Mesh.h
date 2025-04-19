#include <GLAD/glad.h>

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>

#include <string>
#include <vector>


#include "Graphics/Renderer/Shader.h"


#define MAX_BONE_INFLUENCE 4

// ���f�����_�f�[�^
struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
	glm::vec3 Tangent;
	glm::vec3 Bitangent;

	int m_BoneIDs[MAX_BONE_INFLUENCE];
	float m_Weights[MAX_BONE_INFLUENCE];
};

// ���f���e�N�X�`��
struct Texture {
	unsigned int id;
	std::string type;
	std::string path;
};

class Mesh {
public:
	// ���_�f�[�^
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;
	
	// OpenGL �o�b�t�@
	GLuint VAO;

	// �R���X�g���N�^
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);

	// ���f���`��
	void Draw(Shader& shader);

private:
	// OpenGL�o�b�t�@
	GLuint VBO, EBO;
	
	// �o�b�t�@�����Ƒ����ݒ�
	void setupMesh();
};