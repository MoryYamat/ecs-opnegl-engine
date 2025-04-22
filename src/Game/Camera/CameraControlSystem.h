#pragma once

#include <glad/glad.h>

#include "Core/ECS/ECS.h"
#include "Core/ECS/Component/CameraComponent.h"

#include "Game/Input/InputState.h"



namespace GameSystem {
	void CameraControlSystem(ECS& ecs, float deltaTime, const InputState& input);

	void updateCameraVectors(CameraComponent& cam);
}