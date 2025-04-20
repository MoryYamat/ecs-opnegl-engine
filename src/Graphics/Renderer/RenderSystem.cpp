#include "Graphics/Renderer/RenderSystem.h"
#include "Graphics/Renderer/Shader.h"

#include "Core/ECS/Component/TransformComponent.h"
#include "Core/ECS/Component/MeshComponent.h"

void RenderSystem(ECS& ecs, Shader& shader, const glm::mat4& view, const glm::mat4& projection, const Camera& camera) {
	for (auto entity : ecs.view<TransformComponent, MeshComponent, MaterialComponent>()) {
		auto& transform = ecs.get<TransformComponent>(entity);
		auto& mesh = ecs.get<MeshComponent>(entity);
		auto& material = ecs.get<MaterialComponent>(entity);

		shader.use();
		shader.setMat4("model", transform.toMatrix());
		shader.setMat4("view", view);
		shader.setMat4("projection", projection);

		// ライティング
		shader.setVec3("lightPos", glm::vec3(5.0f, 5.0f, 5.0f));
		shader.setVec3("viewPos", camera.getPosition());

		//materialの基本情報
		shader.setVec3("materialColor", material.baseColor);
		shader.setFloat("shininess", material.shininess);

		int unit = 0;
		for (const auto& tex : material.textures)
		{
			glActiveTexture(GL_TEXTURE0 + unit);
			glBindTexture(GL_TEXTURE_2D, tex.id);

			std::string uniformName = "texture_" + tex.type; // "texture_diffuse"
			shader.setInt(uniformName, unit);

			++unit;
		}

		
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

		// 
		for (int i = 0; i < unit; ++i)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}

	//for (auto entity : ecs.view<TransformComponent, MeshComponent, MaterialComponent>())
	//{
	//	auto& transform = ecs.get<TransformComponent>(entity);
	//	auto& mesh = ecs.get<MeshComponent>(entity);
	//	auto& material = ecs.get<MaterialComponent>(entity);

	//	shader.use();
	//	shader.setMat4("model", transform.toMatrix());
	//	shader.setMat4("view", view);
	//	shader.setMat4("projection", projection);

	//	//===テクスチャバインド===
	//	for (unsigned int i = 0; i < material.textures.size(); i++)
	//	{
	//		glActiveTexture(GL_TEXTURE0 + i);
	//		glBindTexture(GL_TEXTURE_2D, material.textures[i].textureID);
	//		shader.setInt(material.textures[i].type, i); // texture_diffuse -> 0番
	//	}

	//	glBindVertexArray(mesh.vao);
	//	glDrawElements(GL_TRIANGLES, mesh.vertexCount, GL_UNSIGNED_INT, 0);
	//	glBindVertexArray(0);
	//	glActiveTexture(GL_TEXTURE0); // リセット
	//}
}