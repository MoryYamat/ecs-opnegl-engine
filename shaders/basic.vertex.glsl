#version 330 core
// position
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;
layout(location = 3) in vec3 aTangent;
layout(location = 4) in vec3 aBitangent;
layout(location = 5) in vec3 boneIDs;
layout(location = 6) in vec3 weights;

out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){
	TexCoord = aTexCoord;
	gl_Position = projection * view * model * vec4(aPos, 1.0);
}