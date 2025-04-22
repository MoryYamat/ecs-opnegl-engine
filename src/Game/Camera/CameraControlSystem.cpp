#include "CameraControlSystem.h"

#include <GLFW/glfw3.h>

#include <glm/gtc/matrix_transform.hpp>
#include <algorithm>

#include "Core/ECS/Component/TransformComponent.h"


void GameSystem::CameraControlSystem(ECS& ecs, float deltaTime, const InputState& input)
{
	for (auto entity : ecs.view<TransformComponent, CameraComponent>())
	{
		auto& transform = ecs.get<TransformComponent>(entity);
		auto& camera = ecs.get<CameraComponent>(entity);

		float velocity = camera.moveSpeed * deltaTime;


		if (input.isPressed(InputAction::MoveForward))
			transform.position += camera.front * velocity;
		if (input.isPressed(InputAction::MoveBackward))
			transform.position -= camera.front * velocity;
		if (input.isPressed(InputAction::MoveRight))
			transform.position += camera.right * velocity;
		if (input.isPressed(InputAction::MoveLeft))
			transform.position -= camera.right * velocity;

		if (input.mouseDelta != glm::vec2(0.0f))
		{
			camera.yaw += input.mouseDelta.x * camera.mouseSensitivity;
			// è„â∫îΩì](OpenGL)
			camera.pitch -= input.mouseDelta.y * camera.mouseSensitivity;

			// pitch êßå¿
			camera.pitch = std::clamp(camera.pitch, -89.0f, 89.0f);
			GameSystem::updateCameraVectors(camera);
		}
	}



}



void GameSystem::updateCameraVectors(CameraComponent& camera)
{
	glm::vec3 front;
	front.x = cos(glm::radians(camera.yaw)) * cos(glm::radians(camera.pitch));
	front.y = sin(glm::radians(camera.pitch));
	front.z = sin(glm::radians(camera.yaw)) * cos(glm::radians(camera.pitch));

	// cam.right = ...........cam.worldup ÅHÅH
	camera.front = glm::normalize(front);
	camera.right = glm::normalize(glm::cross(camera.front, glm::vec3(0.0f, 1.0f, 0.0f)));
	camera.up = glm::normalize(glm::cross(camera.right, camera.front));
}