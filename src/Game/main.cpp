// main.cpp : �A�v���P�[�V�����̃G���g�� �|�C���g���`���܂��B


// GLAD�K���ŏ�(glad�͓�����OpenGL�֐��|�C���^�����������邽��)
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "stb_image.h"

#include <iostream>
#include <filesystem>


#include "Graphics/Renderer/Shader.h"
#include "Game/Camera.h"

// assimip
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

// ECS
#include "Core/ECS/Entity.h"
#include "Core/ECS/ECS.h"

#include "Core/ECS/Component/TransformComponent.h"
#include "Core/ECS/Component/CameraComponent.h"

#include "Graphics/Renderer/RenderSystem.h"

//#include "model.h"

#include "Game/Camera/CameraControlSystem.h"

#include "Game/Input/InputMapping.h"
#include "Game/Input/InputState.h"

#include "Graphics/Model/AssimpImporter.h"
#include "Graphics/Model/ModelRegistry.h"
#include "Graphics/Model/ModelData.h"

//�E�B���h�E�̑傫���ɉ����ĕ`��͈͂Ƒ傫����ύX
//�E�B���h�E�̑傫���ɉ����ĕ`��͈͂Ƒ傫����ύX
//�E�B���h�E�̑傫���ɉ����ĕ`��͈͂Ƒ傫����ύX
// �E�B���h�E�傫��
const unsigned int WIDTH = 1280;
const unsigned int HEIGHT = 760;

InputState inputState;
InputMapping inputMapping;

void resetInputState(InputState& inputState);

//Camera
//Camera camera = Camera();
float lastX = WIDTH / 2.0f;
float lastY = HEIGHT / 2.0f;
bool firstMouse = true;

float aspect = static_cast<float>(WIDTH) / static_cast<float>(HEIGHT);
glm::mat4 projection;

// dletaTime
float deltaTime = 0.0f;
float lastFrame = 0.0f;

//
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

// callbacks
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

bool mouseCaptured = true;

static bool escapeKeyPressedLastFrame = false;

int main()
{

	//GLFW������
	if (!glfwInit()) {
		std::cout << "Failed to initialize GLFW" << std::endl;
		return -1;
	}

	//OpenGL3.3 Coreprofile
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Window�쐬
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Game", nullptr, nullptr);
	if (!window)
	{
		std::cout << "Failed to create window" << std::endl;
		return -1;
	}

	// `window`����ƃR���e�L�X�g�Ɏw��
	glfwMakeContextCurrent(window);


	// glfw: callback
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// tell GLFW to caputure our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//GLAD������
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glEnable(GL_DEPTH_TEST);

	Shader shader("shaders/basic.vertex.glsl", "shaders/basic.fragment.glsl");

	// VAO��VBO�𐶐�
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

	// VAO/VBO�o�C���h����
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	//Model testModel("Assets/Models/Ch44_nonPBR.fbx");



	//====================================================================================
	// ECS �e�X�g�̈�
	//====================================================================================
	std::cout << "====ECS�e�X�g=======" << std::endl;

	ECS ecs;

	Entity e1 = ecs.createEntity();
	Entity testmodel = ecs.createEntity();


	//Transform�o�^
	TransformComponent transformComponent;
	transformComponent.position = glm::vec3(4.0f, 4.0f, -10.0f);


	ecs.addComponent<TransformComponent>(e1, transformComponent);

	transformComponent.position = glm::vec3(0.0f, 0.0f, 0.0f);
	ecs.addComponent<TransformComponent>(testmodel, transformComponent);


	//==============================Camera==============================
	// CameraComponent
	Entity cameraEntity = ecs.createEntity();

	TransformComponent camTransform;
	camTransform.position = glm::vec3(0.0f, 0.0f, 10.0f);
	camTransform.rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	camTransform.scale = glm::vec3(1.0f);
	ecs.addComponent<TransformComponent>(cameraEntity, camTransform);

	ecs.addComponent<CameraComponent>(cameraEntity, CameraComponent{});

	//==============================Camera===============================

	AssimpImporter importer;
	ModelData model = importer.Import("Assets/Models/Ch44_nonPBR.fbx");

	ModelRegistry registry;
	registry.RegisterModelToECS(ecs, model);

	//std::cout << "modelVerticesPos.x: " << model.meshes[0].vertices[0].position.x << std::endl;

	//Mesh�o�^
	//Mesh mesh;
	//mesh.vao = VAO;
	//mesh.vbo = VBO;
	//mesh.vertexCount = 36;
	//ecs.addComponent<Mesh>(e1, mesh);
	//ecs.addComponent<Mesh>(e2, mesh);

	// Entity�Ƃ���3D���f����o�^���āA�����炩��`����s����悤�ɉ��ǂ���B
	// Entity�Ƃ���3D���f����o�^���āA�����炩��`����s����悤�ɉ��ǂ���B
	// Entity�Ƃ���3D���f����o�^���āA�����炩��`����s����悤�ɉ��ǂ���B
	// Entity�Ƃ���3D���f����o�^���āA�����炩��`����s����悤�ɉ��ǂ���B
	// Entity�Ƃ���3D���f����o�^���āA�����炩��`����s����悤�ɉ��ǂ���B

	

	//====================================================================================
	// ECS �e�X�g�̈� �I��
	//====================================================================================

	//���C�����[�v
	while (!glfwWindowShouldClose(window))
	{
		//deltaTime
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;




		//window aspect



		//
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // �� ���[�x�o�b�t�@���N���A����I

		//renderer
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Entity�Ƃ���3D���f����o�^���āA�����炩��`����s����悤�ɉ��ǂ���B
		// Entity�Ƃ���3D���f����o�^���āA�����炩��`����s����悤�ɉ��ǂ���B
		// Entity�Ƃ���3D���f����o�^���āA�����炩��`����s����悤�ɉ��ǂ���B
		// Entity�Ƃ���3D���f����o�^���āA�����炩��`����s����悤�ɉ��ǂ���B
		// Entity�Ƃ���3D���f����o�^���āA�����炩��`����s����悤�ɉ��ǂ���B

		inputMapping.update(window, inputState);
		if (inputState.actions[InputAction::Quit]) break;

		GameSystem::CameraControlSystem(ecs, deltaTime, inputState);

		RenderSystem::RenderSystem(ecs, shader, aspect);

		resetInputState(inputState);

		//---------------------------------------
		// glfw: buffer
		glfwSwapBuffers(window);

		// poll envents
		glfwPollEvents();
	}


	// �I��
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}


// glfw: �E�B���h�E�T�C�Y���ύX���ꂽ�Ƃ����s�����
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// 
	glViewport(0, 0, width, height);

	// 
	aspect = static_cast<float>(width) / static_cast<float>(height);
	//camera.GetProjectionMatrix(aspect);
	std::cout << "Changed Window size: "
		<< " width: " << width
		<< ", height: " << height
		<< ", aspect: " << aspect;

}



// glfw: whenever the mouse moves, this callback is called
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
	//float xpos = static_cast<float>(xposIn);
	//float ypos = static_cast<float>(yposIn);

	//if (firstMouse)
	//{
	//	lastX = xpos;
	//	lastY = ypos;
	//	firstMouse = false;
	//}

	//float xoffset = xpos - lastX;
	//float yoffset = lastY - ypos;

	//lastX = xpos;
	//lastY = ypos;


	//inputState.mouseDelta = glm::vec2(xoffset, yoffset);
	//inputState.mousePosition = glm::vec2(xpos, ypos);

	//camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	//camera.ProcessMouseScroll(static_cast<float>(yoffset));
	//inputState.scrollDelta = static_cast<float>(yoffset);
}

void resetInputState(InputState& inputState)
{
	inputState.mouseDelta = glm::vec2(0.0f);
	inputState.scrollDelta = 0.0f;
}

//==================================ECS=============================
// Entity : ID
// Component: Data
// System : �����Component�̏W����������Entity�̐U�镑�������߂�
// 
// ������`Component`��`Entity`�̐������` 
// -> `Component`�̏W�����T�O���`���
//
// ����`�T�O`�̐U�镑�����`����̂�`System`
// ����ɂ���āA�S�Ă�`�I�u�W�F�N�g`��`�U�镑��`��
// `ECS`�ɂ���Ē�`����
//
//
// �Ӑ}���������ۏ؂��邽�߂ɁAEntity������Â���Component���`���A
// ����ɉ�����System�����K�v������B
//
//
//
//
//==================================ECS=============================