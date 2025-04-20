#pragma once

#include "Core/ECS/ECS.h"
#include "Graphics/Model/ModelData.h"


class ModelRegistry {
public:

	static void RegisterModelToECS(ECS& ecs, const ModelData& model);
};