#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>


// Mesh: VAO, VBO, 頂点数を保持(Entityが何をどう描くかの情報)
struct MeshComponent {
	GLuint vao = 0;//GLuint => unsigned int
	GLuint vbo = 0;
	GLuint ebo = 0;

	int vertexCount = 0;
	bool hasIndices = true;
};