#include "RenderSystem.h"
#include "Shader.h"

void RenderSystem(ECS& ecs, Shader& shader, const glm::mat4& view, const glm::mat4& projection) {
	for (auto entity : ecs.view<Transform, Mesh>()) {
		auto& transform = ecs.get<Transform>(entity);
		auto& mesh = ecs.get<Mesh>(entity);

		shader.use();
		shader.setMat4("model", transform.toMatrix());
		shader.setMat4("view", view);
		shader.setMat4("projection", projection);

		glBindVertexArray(mesh.vao);
		glDrawArrays(GL_TRIANGLES, 0, mesh.vertextCount);
		glBindVertexArray(0);
	}
}