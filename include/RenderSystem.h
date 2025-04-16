#pragma once
#include <glm/glm.hpp>

#include "Shader.h"
#include "ECS.h"
#include "Component.h"

void RenderSystem(ECS& ecs, Shader& shader, const glm::mat4& view, const glm::mat4& projection);