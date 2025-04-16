#include "RenderSystem.h"
#include "Shader.h"


void RenderSystem(ECS& ecs, Shader& shader, const glm::mat4& view, const glm::mat4& projection) {
	for (auto entity : ecs.view<TransformComponent, MeshComponent>()) {
		auto& transform = ecs.get<TransformComponent>(entity);
		auto& mesh = ecs.get<MeshComponent>(entity);

		shader.use();
		shader.setMat4("model", transform.toMatrix());
		shader.setMat4("view", view);
		shader.setMat4("projection", projection);

		glBindVertexArray(mesh.vao);
		glDrawArrays(GL_TRIANGLES, 0, mesh.vertexCount);
		glBindVertexArray(0);
	}
}