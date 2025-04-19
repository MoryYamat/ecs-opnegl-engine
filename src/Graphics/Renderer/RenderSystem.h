#pragma once
#include <glm/glm.hpp>

#include "Shader.h"
#include "ECS/ECS.h"
#include "ECS/Component/TransformComponent.h"
#include "ECS/Component/MeshComponent.h"

void RenderSystem(ECS& ecs, Shader& shader, const glm::mat4& view, const glm::mat4& projection);