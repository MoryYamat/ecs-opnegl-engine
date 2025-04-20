#include "GPUBufferUtils.h"

#include <GLAD/glad.h>


namespace GPUBufferUtils {
	MeshComponent createMeshComponentFromMeshData(const MeshData& mesh) 
	{
		MeshComponent component;

		glGenVertexArrays(1, &component.vao);
		glGenBuffers(1, &component.vbo);

		glBindVertexArray(component.vao);

		// 頂点バッファ
		glBindBuffer(GL_ARRAY_BUFFER, component.vbo);
		glBufferData(GL_ARRAY_BUFFER, mesh.vertices.size() * sizeof(Vertex),
			&mesh.vertices[0], GL_STATIC_DRAW);


		// インデックスバッファ
		component.hasIndices = !mesh.indices.empty();
		if (component.hasIndices)
		{
			glGenBuffers(1, &component.ebo);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, component.ebo);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.indices.size() * sizeof(unsigned int),
				&mesh.indices[0], GL_STATIC_DRAW);
		}


		GLsizei stride = sizeof(Vertex);

		// layout(location = 0) position
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)offsetof(Vertex, position));

		// layout(location = 1) position
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)offsetof(Vertex, normal));

		// layout(location = 2) position
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)offsetof(Vertex, texCoords));

		// layout(location = 3) position
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, stride, (void*)offsetof(Vertex, tangent));

		// layout(location = 4) position
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, stride, (void*)offsetof(Vertex, bitangent));

		// layout(location = 5) position
		glEnableVertexAttribArray(5);
		glVertexAttribPointer(5, 4, GL_INT, GL_FALSE, stride, (void*)offsetof(Vertex, boneIDs));

		// layout(location = 6) position
		glEnableVertexAttribArray(6);
		glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, stride, (void*)offsetof(Vertex, weights));

		glBindVertexArray(0);

		component.vertexCount = component.hasIndices ?
			static_cast<int>(mesh.indices.size()) :
			static_cast<int>(mesh.vertices.size());

		return component;
	}
}