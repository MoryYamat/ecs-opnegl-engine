#pragma once
#include <glm/glm.hpp>

#include "Shader.h"
#include "ECS/ECS.h"
#include "ECS/Component/Component.h"

void RenderSystem(ECS& ecs, Shader& shader, const glm::mat4& view, const glm::mat4& projection);