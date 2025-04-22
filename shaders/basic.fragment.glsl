#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec2 TexCoord;
in mat3 TBN;

uniform sampler2D texture_diffuse;
uniform sampler2D texture_specular;
uniform sampler2D texture_normal;

uniform vec3 materialColor;
uniform float shininess;

// 簡単なライト
uniform vec3 lightPos;
uniform vec3 viewPos;

void main(){
	// テクスチャのノーマルマップを取得
	vec3 normal = texture(texture_normal, TexCoord).rgb;
	normal = normalize(normal * 2.0 - 1.0);
	normal = normalize(TBN * normal);

	// 法線ベクトルと光ベクトル
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(normal, lightDir), 0.0);

	//　拡散光
	vec3 diffuseTex = texture(texture_diffuse, TexCoord).rgb;
	vec3 diffuse = diff * diffuseTex;

	// 鏡面
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
	vec3 specularTex = texture(texture_specular, TexCoord).rgb;
	vec3 specular = spec * specularTex;

	vec3 ambient = 0.1 * diffuseTex;


	//vec3 debugNormal = normalize(TBN[2]);
	//vec3 debugNormal = texture(texture_normal, TexCoord).rgb;

	vec3 result = ambient + diffuse + specular;
	//FragColor= vec4(debugNormal, 1.0);
	
	FragColor = vec4(result, 1.0);

}