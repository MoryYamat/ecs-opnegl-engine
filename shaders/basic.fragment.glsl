#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

uniform sampler2D texture_diffuse;
uniform sampler2D texture_specular;
uniform vec3 materialColor;
uniform float shininess;

// 簡単なライト
uniform vec3 lightPos;
uniform vec3 viewPos;

void main(){
	// 法線ベクトルと光ベクトル
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);

	//　拡散光
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuseTex = texture(texture_diffuse, TexCoord).rgb;
	vec3 diffuse = diff * diffuseTex;

	// 鏡面
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
	vec3 specularTex = texture(texture_specular, TexCoord).rgb;
	vec3 specular = spec * specularTex;

	vec3 ambient = 0.1 * diffuseTex;
	vec3 result = ambient + diffuse + specular;

	FragColor = vec4(result, 1.0);

}