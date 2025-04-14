#pragma once

#include "ECS.h"
#include "Component.h"
#include "Shader.h"
#include <glm/glm.hpp>

void RenderSystem(ECS& ecs, Shader& shader, const glm::mat4& view, const glm::mat4& projection);