#pragma once

#

#include "Core/ECS/ECS.h"
#include "Graphics/Model/ModelData.h"


class ModelRegistry {
public:

	static void RegisterModelToECS(ECS& ecs, const ModelData& model, const glm::vec3& position, const glm::vec3 rotation, const glm::vec3& scale);
};