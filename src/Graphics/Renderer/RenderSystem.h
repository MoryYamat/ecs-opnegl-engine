#pragma once
#include <glm/glm.hpp>

#include "Graphics/Renderer/Shader.h"
#include "Core/ECS/ECS.h"
#include "Core/ECS/Component/TransformComponent.h"
#include "Core/ECS/Component/MeshComponent.h"

void RenderSystem(ECS& ecs, Shader& shader, const glm::mat4& view, const glm::mat4& projection);