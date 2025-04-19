#pragma once


#include <glad/glad.h>
#include <glm/glm.hpp>

#include <GLM/gtc/matrix_transform.hpp>



// Transform: Position, Rotation, Scale(位置・回転・スケール)
struct TransformComponent {
	glm::vec3 position = glm::vec3(0.0f);
	glm::vec3 rotation = glm::vec3(0.0f);
	glm::vec3 scale = glm::vec3(1.0f);

	//モデル変換行列
	glm::mat4 toMatrix() const {
			glm::mat4 model = glm::translate(glm::mat4(1.0f), position);// 並進
			model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1, 0, 0));// 回転
			model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0, 1, 0));
			model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0, 0, 1));
			model = glm::scale(model, scale);// スケール
			return model;
	}
};



// Texture: OpenGLのテクスチャIDを保持
struct TextureComponent {
	GLuint id = 0;
};