#include "Graphics/Renderer/RenderSystem.h"
#include "Graphics/Renderer/Shader.h"

//#include "Core/ECS/Component/TransformComponent.h"
#include "Core/ECS/Component/MeshComponent.h"

	//void RenderSystem(ECS& ecs, Shader& shader, const glm::mat4& view, const glm::mat4& projection, const Camera& camera) {
void RenderSystem::RenderSystem(ECS& ecs, Shader& shader, float aspect)
{
	glm::mat4 view, projection;

	if (!getCameraMatrices(ecs, aspect, view, projection))
	{
		std::cout << "[RenderSystem] No valid camera found in ECS. " << std::endl;
		return;
	}


	for (auto entity : ecs.view<TransformComponent, MeshComponent, MaterialComponent>()) {
		auto& transform = ecs.get<TransformComponent>(entity);
		auto& mesh = ecs.get<MeshComponent>(entity);
		auto& material = ecs.get<MaterialComponent>(entity);

		shader.use();
		shader.setMat4("model", transform.toMatrix());
		shader.setMat4("view", view);
		shader.setMat4("projection", projection);

		// ライティング
		//shader.setVec3("lightPos", glm::vec3(0.0f, 500.0f, 500.0f));
		//shader.setVec3("viewPos", camera.getPosition());


		applyMaterialToShader(material, shader);

		drawMesh(mesh);
	}

}

void RenderSystem::applyMaterialToShader(const MaterialComponent& material, Shader& shader)
{
	//materialの基本情報
	shader.setVec3("materialColor", material.baseColor);
	shader.setFloat("shininess", material.shininess);

	int unit = 0;
	for (const auto& tex : material.textures)
	{
		glActiveTexture(GL_TEXTURE0 + unit);
		glBindTexture(GL_TEXTURE_2D, tex.id);

		std::string uniformName = "texture_" + tex.type; // "texture_diffuse"

		//std::cout << uniformName << std::endl;

		shader.setInt(uniformName, unit);

		++unit;
	}



	// 
	for (int i = 0; i < unit; ++i)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

}


void RenderSystem::drawMesh(const MeshComponent& mesh)
{
	glBindVertexArray(mesh.vao);
	if (mesh.hasIndices)
	{
		glDrawElements(GL_TRIANGLES, mesh.vertexCount, GL_UNSIGNED_INT, 0);
		//std::cout << "draw elements " << std::endl;
	}
	else
	{
		glDrawArrays(GL_TRIANGLES, 0, mesh.vertexCount);
		//std::cout << "draw Arrays" << std::endl;
	}
	glBindVertexArray(0);
}

bool RenderSystem::getCameraMatrices(ECS& ecs, float aspect, glm::mat4& view, glm::mat4& projection)
{
	TransformComponent* camTransform = nullptr;
	CameraComponent* camData = nullptr;

	for (auto entity : ecs.view<TransformComponent, CameraComponent>())
	{
		camTransform = &ecs.get<TransformComponent>(entity);
		camData = &ecs.get<CameraComponent>(entity);
		break;
	}

	if (!camTransform || !camData)
	{
		std::cout << "No Camera found !" << std::endl;
		return false;
	}

	view = computeViewMatrix(*camTransform, *camData);
	projection = computeProjectionMatrix(camData->fov, aspect, camData->nearClip, camData->farClip);

	return true;
}


glm::mat4 RenderSystem::computeViewMatrix(const TransformComponent& transform, const CameraComponent& camera)
{
	glm::vec3 position = transform.position;
	return glm::lookAt(position, position + camera.front, camera.up);
}

glm::mat4 RenderSystem::computeProjectionMatrix(float fov, float aspect, float nearClip, float farClip)
{
	return glm::perspective(glm::radians(fov), aspect, nearClip, farClip);
}