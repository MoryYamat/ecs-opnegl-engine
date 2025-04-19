#include <GLAD/glad.h>

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>

#include <string>
#include <vector>


#include "Graphics/Renderer/Shader.h"


#define MAX_BONE_INFLUENCE 4

// モデル頂点データ
struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
	glm::vec3 Tangent;
	glm::vec3 Bitangent;

	int m_BoneIDs[MAX_BONE_INFLUENCE];
	float m_Weights[MAX_BONE_INFLUENCE];
};

// モデルテクスチャ
struct Texture {
	unsigned int id;
	std::string type;
	std::string path;
};

class Mesh {
public:
	// 頂点データ
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;
	
	// OpenGL バッファ
	GLuint VAO;

	// コンストラクタ
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);

	// モデル描画
	void Draw(Shader& shader);

private:
	// OpenGLバッファ
	GLuint VBO, EBO;
	
	// バッファ生成と属性設定
	void setupMesh();
};