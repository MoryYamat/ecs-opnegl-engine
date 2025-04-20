#pragma once
#include <glm/glm.hpp>

#include "Graphics/Renderer/Shader.h"
#include "Core/ECS/ECS.h"

#include "Core/ECS/Component/MaterialComponent.h"

#include "Game/Camera.h"



void RenderSystem(ECS& ecs, Shader& shader, const glm::mat4& view, const glm::mat4& projection, const Camera& camera);


//inline void ApplyMaterialToShader(const MaterialComponent& material, Shader& shader) 
//{
//	int textureUnit = 0;
//
//	for (const auto& tex : material.textures) {
//		glActiveTexture(GL_TEXTURE0 + textureUnit);
//		glBindTexture(GL_TEXTURE_2D, tex.id);
//		shader.setInt(tex.type, textureUnit);
//		textureUnit++;
//	}
//
//	/*shader.setVec3("material.baseColor", material.baseColor);
//	shader.setFloat("material.shininess", material.shininess);*/
//
//	glActiveTexture(GL_TEXTURE0);
//}