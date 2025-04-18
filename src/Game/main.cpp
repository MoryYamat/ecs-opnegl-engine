// main.cpp : アプリケーションのエントリ ポイントを定義します。


// GLAD必ず最初(gladは内部でOpenGL関数ポインタを初期化するため)
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <iostream>
#include <filesystem>


#include "Graphics/Renderer/Shader.h"
#include "Camera.h"

// assimip
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

// ECS
#include "Core/ECS/Entity.h"
#include "Core/ECS/ECS.h"
#include "Core/ECS/Component/TransformComponent.h"

#include "Graphics/Renderer/RenderSystem.h"

//#include "model.h"

#include "Graphics/Model/AssimpImporter.h"

#include "Graphics/Model/ModelData.h"

//ウィンドウの大きさに応じて描画範囲と大きさを変更
//ウィンドウの大きさに応じて描画範囲と大きさを変更
//ウィンドウの大きさに応じて描画範囲と大きさを変更
// ウィンドウ大きさ
const unsigned int WIDTH = 1280;
const unsigned int HEIGHT = 760;



//Camera
Camera camera = Camera();
float lastX = WIDTH / 2.0f;
float lastY = HEIGHT / 2.0f;
bool firstMouse = true;

float aspect = static_cast<float>(WIDTH) / static_cast<float>(HEIGHT);
glm::mat4 projection;

// dletaTime
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// テスト用頂点データ
float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

glm::vec3 cubePositions[] = {
	glm::vec3(0.0f, 0.0f, 0.0f)
};

//
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// callbacks
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

bool mouseCaptured = true;

static bool escapeKeyPressedLastFrame = false;

int main()
{

	//GLFW初期化
	if (!glfwInit()) {
		std::cout << "Failed to initialize GLFW" << std::endl;
		return -1;
	}

	//OpenGL3.3 Coreprofile
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Window作成
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Game", nullptr, nullptr);
	if (!window)
	{
		std::cout << "Failed to create window" << std::endl;
		return -1;
	}

	// `window`を作業コンテキストに指定
	glfwMakeContextCurrent(window);


	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// tell GLFW to caputure our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//GLAD初期化
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glEnable(GL_DEPTH_TEST);

	Shader shader("shaders/basic.vertex.glsl", "shaders/basic.fragment.glsl");

	// VAOとVBOを生成
	//unsigned int VAO, VBO;
	//glGenVertexArrays(1, &VAO);
	//glGenBuffers(1, &VBO);

	//glBindVertexArray(VAO);

	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);

	//glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(1);

	//unsigned int texture;
	//glGenTextures(1, &texture);
	//glBindTexture(GL_TEXTURE_2D, texture);

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	unsigned char* data = stbi_load("Assets/Textures/container.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to lead texture" << std::endl;
	}
	stbi_image_free(data);

	// VAO/VBOバインド解除
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	//Model testModel("Assets/Models/Ch44_nonPBR.fbx");



	//====================================================================================
	// ECS テスト領域
	//====================================================================================
	std::cout << "====ECSテスト=======" << std::endl;

	ECS ecs;

	Entity e1 = ecs.createEntity();
	Entity testmodel = ecs.createEntity();

	//Transform登録
	TransformComponent transformComponent;
	transformComponent.position = glm::vec3(4.0f, 4.0f, -10.0f);


	ecs.addComponent<TransformComponent>(e1, transformComponent);

	transformComponent.position = glm::vec3(0.0f, 0.0f, 0.0f);
	ecs.addComponent<TransformComponent>(testmodel, transformComponent);

	/*const Mesh& mesh = testModel.getMeshes()[0];

	MeshComponent modelMesh;
	modelMesh.vao = mesh.VAO;
	modelMesh.vertexCount = static_cast<int>(mesh.indices.size());
	ecs.addComponent<MeshComponent>(testmodel, modelMesh);*/

	//AssimpImporter::Import("Assets/Models/Ch44_nonPBR.fbx");
	AssimpImporter importer;
	ModelData model = importer.Import("Assets/Models/Ch44_nonPBR.fbx");

	std::cout << "modelVerticesPos.x: " << model.meshes[0].vertices[0].position.x << std::endl;

	//Mesh登録
	//Mesh mesh;
	//mesh.vao = VAO;
	//mesh.vbo = VBO;
	//mesh.vertexCount = 36;
	//ecs.addComponent<Mesh>(e1, mesh);
	//ecs.addComponent<Mesh>(e2, mesh);

	// Entityとして3Dモデルを登録して、そちらから描画を行えるように改良する。
	// Entityとして3Dモデルを登録して、そちらから描画を行えるように改良する。
	// Entityとして3Dモデルを登録して、そちらから描画を行えるように改良する。
	// Entityとして3Dモデルを登録して、そちらから描画を行えるように改良する。
	// Entityとして3Dモデルを登録して、そちらから描画を行えるように改良する。

	

	//====================================================================================
	// ECS テスト領域 終了
	//====================================================================================

	//メインループ
	while (!glfwWindowShouldClose(window))
	{
		//deltaTime
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		//input
		processInput(window);

		//window aspect



		//
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // ← ★深度バッファもクリアする！

		//renderer
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//描画処理
		//glBindTexture(GL_TEXTURE_2D, texture);

		//オブジェクトを描画
		shader.use();
		//shader.setInt("ourTexture", 0);

		glm::mat4 modelMat = glm::mat4(1.0f);
		modelMat = glm::scale(modelMat, glm::vec3(0.01f));
		shader.setMat4("model", modelMat);

		// Entityとして3Dモデルを登録して、そちらから描画を行えるように改良する。
		// Entityとして3Dモデルを登録して、そちらから描画を行えるように改良する。
		// Entityとして3Dモデルを登録して、そちらから描画を行えるように改良する。
		// Entityとして3Dモデルを登録して、そちらから描画を行えるように改良する。
		// Entityとして3Dモデルを登録して、そちらから描画を行えるように改良する。
		//testModel.Draw(shader);

		//ビュー変換行列
		glm::mat4 view = camera.GetViewMatrix();
		//投影行列
		glm::mat4 projection = camera.GetProjectionMatrix(aspect);

		shader.setMat4("projection", projection);

		shader.setMat4("view", view);



		//glm::mat4 model = glm::mat4(1.0f);
		//model = glm::translate(model, cubePositions[0]);
		//shader.setMat4("model", model);

		RenderSystem(ecs, shader, view, projection);



		//---------------------------------------
		// glfw: buffer
		glfwSwapBuffers(window);

		// poll envents
		glfwPollEvents();
	}


	// 終了
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}


// glfw: ウィンドウサイズが変更されたとき実行される
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// 
	glViewport(0, 0, width, height);

	// 
	aspect = static_cast<float>(width) / static_cast<float>(height);
	camera.GetProjectionMatrix(aspect);
	std::cout << "Changed Window size: "
		<< " width: " << width
		<< ", height: " << height
		<< ", aspect: " << aspect;

}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	// movement
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(Camera_Movement::FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(Camera_Movement::BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(Camera_Movement::RIGHT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(Camera_Movement::LEFT, deltaTime);

	// mouse capture 
	int escapeKeyState = glfwGetKey(window, GLFW_KEY_ESCAPE);
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS && !escapeKeyPressedLastFrame)
		if (mouseCaptured)
		{
			// Enable Moues Capture
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			mouseCaptured = false;

			firstMouse = true;
		}
		else 
		{
			// Disable Mouse Capture
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			mouseCaptured = true;
		}

	escapeKeyPressedLastFrame = (escapeKeyState == GLFW_PRESS);
	//std::cout << "escapeKeyState:  " << escapeKeyState << std::endl;
}


// glfw: whenever the mouse moves, this callback is called
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(static_cast<float>(yoffset));
}