#pragma once
#include <glm/glm.hpp>

#include "Graphics/Renderer/Shader.h"
#include "Core/ECS/ECS.h"

#include "Core/ECS/Component/TransformComponent.h"
#include "Core/ECS/Component/MaterialComponent.h"
#include "Core/ECS/Component/MeshComponent.h"
#include "Core/ECS/Component/CameraComponent.h"

#include "Game/Camera.h"

namespace RenderSystem {
	//
//void RenderSystem(ECS& ecs, Shader& shader, const glm::mat4& view, const glm::mat4& projection, const Camera& camera);
	void RenderSystem(ECS& ecs, Shader& shader, float aspect);

	bool getCameraMatrices(ECS& ecs, float aspect, glm::mat4& view, glm::mat4& projection);

	void applyMaterialToShader(const MaterialComponent& material, Shader& shader);

	void drawMesh(const MeshComponent& mesh);

	glm::mat4 computeViewMatrix(const TransformComponent& transform, const CameraComponent& camera);

	glm::mat4 computeProjectionMatrix(float fov, float aspect, float nearClip, float farClip);

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
}

