#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <map>
#include <vector>

struct TextureSlot {
	std::string type;// "diffuse" , "specular", "normal", "height"
	GLuint id;// OpenGL Texture ID
};

struct MaterialComponent {
	// texture slot vector
	std::vector<TextureSlot> textures;

	// default color
	glm::vec3 baseColor = glm::vec3(1.0f);// white
	float shininess = 32.0f;

	// option
	bool useTexture = true;

	//std::unordered_map<std::string, GLuint> textureIDs;// "diffuse" -> GLuint
	//std::unordered_map<std::string, glm::vec3> vec3Params;// "baseColor" -> vec3
	//std::unordered_map<std::string, float> floatParams;// "roughness" -> 0.5
};