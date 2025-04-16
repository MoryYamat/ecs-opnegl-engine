#pragma once


#include <glad/glad.h>
#include <glm/glm.hpp>

#include <GLM/gtc/matrix_transform.hpp>



// Transform: Position, Rotation, Scale(�ʒu�E��]�E�X�P�[��)
struct Transform {
	glm::vec3 position = glm::vec3(0.0f);
	glm::vec3 rotation = glm::vec3(0.0f);
	glm::vec3 scale = glm::vec3(1.0f);

	//���f���ϊ��s��
	glm::mat4 toMatrix() const {
			glm::mat4 model = glm::translate(glm::mat4(1.0f), position);// ���i
			model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1, 0, 0));// ��]
			model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0, 1, 0));
			model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0, 0, 1));
			model = glm::scale(model, scale);// �X�P�[��
			return model;
	}
};

// Mesh: VAO, VBO, ���_����ێ�(Entity�������ǂ��`�����̏��)
struct Mesh {
	GLuint vao = 0;//GLuint => unsigned int
	GLuint vbo = 0;
	//GLuint ebo = 0;

	int vertextCount = 0;
};

// Texture: OpenGL�̃e�N�X�`��ID��ێ�
struct Texture {
	GLuint id = 0;
};