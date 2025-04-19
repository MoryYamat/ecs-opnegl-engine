#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>


// Mesh: VAO, VBO, ���_����ێ�(Entity�������ǂ��`�����̏��)
struct MeshComponent {
	GLuint vao = 0;//GLuint => unsigned int
	GLuint vbo = 0;
	GLuint ebo = 0;

	int vertexCount = 0;
};