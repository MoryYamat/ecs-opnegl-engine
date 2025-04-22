#pragma once
#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>



struct CameraComponent {
	// 撮影用パラメータ

	float fov = 45.0f;
	float nearClip = 0.1f;
	float farClip = 1000.0f;

	// camera param
	float yaw = -90.0f;
	float pitch = 0.0f;

	glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 right = glm::vec3(1.0f, 0.0f, 0.0f);

	float moveSpeed = 5.0f;
	float mouseSensitivity = 0.1f;
};