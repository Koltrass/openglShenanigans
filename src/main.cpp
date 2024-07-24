#include <iostream>
#include <vector>
#include <string>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION

#include "Shader.h"
#include "Camera.h"
#include "Cube.h"
#include "Spotlight.h"
#include "PointLight.h"
#include "DirectionLight.h"
#include "TextureLoader.h"
#include "Model.h"
#define FULLSCREEN 1

float mixVal = 0.5f;

#if FULLSCREEN == 1
int width = 1920;
int height = 1080;
#else
int width = 800;
int height = 600;
#endif

Camera camera(0.0f, 5.0f, 3.0f, 0.0f, 1.0f, 0.0f, -90.0f, 0.0f);
float deltaTime = 0.0f;
float lastFrame = 0.0f;

float lastX = width / 2.0f;
float lastY = height / 2.0f;
bool firstMouse = true;

std::vector<std::unique_ptr<Spotlight>> spotlights;

int selectedPointLight = 0;
std::vector<std::unique_ptr<PointLight>> pointLights;

DirectionLight directionLight(glm::vec3(1.0f, 1.0f, 1.0f),
	glm::vec3(0.0f, -1.0f, 0.2f));

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xPos, double yPos);
void scroll_callback(GLFWwindow* window, double xOffset, double yOffset);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void processInput(GLFWwindow* window);
int main()
{
	spotlights.push_back(std::make_unique<Spotlight>
		(
			glm::vec3(1.0f, 1.0f, 1.0f),
			glm::vec3(-5.75f, 5.75f, 0.0f), glm::vec3(0.5f, -1.0f, 0.0f),
			glm::vec3(1.0f, 0.09f, 0.032f), 30.0f, 45.0f
		));
	pointLights.push_back(std::make_unique<PointLight>
		(
			glm::vec3(1.0f, 0.0f, 0.0f),
			glm::vec3(9.0f, 10.0f, 0.0f),
			glm::vec3(1.0f, 0.22f, 0.20f)
		));
	pointLights.push_back(std::make_unique<PointLight>
		(
			glm::vec3(1.0f, 0.0f, 1.0f),
			glm::vec3(9.0f, 6.0f, 5.0f),
			glm::vec3(1.0f, 0.22f, 0.20f)
		));

	float vertices[] = {
		// positions            // normals            // texture coords
		-0.5f, -0.5f, -0.5f,    0.0f,  0.0f, -1.0f,    0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,    0.0f,  0.0f, -1.0f,    1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,    0.0f,  0.0f, -1.0f,    1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,    0.0f,  0.0f, -1.0f,    1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,    0.0f,  0.0f, -1.0f,    0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,    0.0f,  0.0f, -1.0f,    0.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  1.0f,    0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  1.0f,    1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,    0.0f,  0.0f,  1.0f,    1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,    0.0f,  0.0f,  1.0f,    1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,    0.0f,  0.0f,  1.0f,    0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  1.0f,    0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,   -1.0f,  0.0f,  0.0f,    1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,   -1.0f,  0.0f,  0.0f,    1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,   -1.0f,  0.0f,  0.0f,    0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,   -1.0f,  0.0f,  0.0f,    0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,   -1.0f,  0.0f,  0.0f,    0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,   -1.0f,  0.0f,  0.0f,    1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,    1.0f,  0.0f,  0.0f,    1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,    1.0f,  0.0f,  0.0f,    1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,    1.0f,  0.0f,  0.0f,    0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,    1.0f,  0.0f,  0.0f,    0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,    1.0f,  0.0f,  0.0f,    0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,    1.0f,  0.0f,  0.0f,    1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,    0.0f, -1.0f,  0.0f,    0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,    0.0f, -1.0f,  0.0f,    1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,    0.0f, -1.0f,  0.0f,    1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,    0.0f, -1.0f,  0.0f,    1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,    0.0f, -1.0f,  0.0f,    0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,    0.0f, -1.0f,  0.0f,    0.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,    0.0f,  1.0f,  0.0f,    0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,    0.0f,  1.0f,  0.0f,    1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,    0.0f,  1.0f,  0.0f,    1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,    0.0f,  1.0f,  0.0f,    1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,    0.0f,  1.0f,  0.0f,    0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,    0.0f,  1.0f,  0.0f,    0.0f, 1.0f
	};
	Cube cubes[] =
	{
		{ { -2.0f,  5.0f, 0.0f }, 1.0f, 2048.0f },
		{ { -2.0f,  3.0f, 0.0f }, 1.0f, 2048.0f },
		{ { -2.0f,  1.0f, 0.0f }, 1.0f, 2048.0f },
		{ {  0.0f,  3.0f, 0.0f }, 1.0f, 2048.0f },
		{ {  0.0f,  1.0f, 0.0f }, 1.0f, 2048.0f },
		{ {  2.0f,  5.0f, 0.0f }, 1.0f, 2048.0f },
		{ {  0.0f,  5.0f, 0.0f }, 1.0f, 2048.0f },
		{ {  2.0f,  3.0f, 0.0f }, 1.0f, 2048.0f },
		{ {  2.0f,  1.0f, 0.0f }, 1.0f, 2048.0f },
		{ {  10.0f, 5.0f, 0.0f }, 8.0f, 2048.0f },
		{ {  0.0f,  -50.0, 0.0f }, 100.0f, 2048.0f}
	};

	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#if FULLSCREEN == 1
	GLFWwindow* window = glfwCreateWindow(width, height, "Small window", glfwGetPrimaryMonitor(), NULL);
#else
	GLFWwindow* window = glfwCreateWindow(width, height, "Small window", NULL, NULL);
#endif
	if (window == NULL)
	{
		std::cout << "Failed to create a window\n";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD\n";
		return -1;
	}
	glViewport(0, 0, width, height);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetKeyCallback(window, key_callback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	unsigned int VAO1;
	glGenVertexArrays(1, &VAO1);
	glBindVertexArray(VAO1);

	unsigned int VBO1;
	glGenBuffers(1, &VBO1);
	glBindBuffer(GL_ARRAY_BUFFER, VBO1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);


	unsigned int textureContainerDiffuse = TextureLoader::loadTexture("Textures/container2.png");
	unsigned int textureContainerSpecular = TextureLoader::loadTexture("Textures/container2_specular.png");
	unsigned int textureLampPost = TextureLoader::loadTexture("Textures/lampPost_diffuse.png");

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


	Shader shaderCube("Shaders/Vertex/lightingPracticeObject.vert", "Shaders/Fragment/lightingPracticeObject.frag");
	Shader shaderLightSource("Shaders/Vertex/lightingPracticeObject.vert", "Shaders/Fragment/lightingPracticeSource.frag");
	Shader modelTest("Shaders/Vertex/lightingPracticeObject.vert", "Shaders/Fragment/modelLearning.frag");

	Model backpack("Assets/Models/backpack/backpack.obj");

	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		glm::mat4 view = glm::mat4(1.0f);
		view = camera.getViewMatrix();

		glm::mat4 projection = glm::mat4(1.0f);
		//projection = glm::ortho(-(float)width/height, (float)width/height, -1.0f, 1.0f, 0.1f, 100.0f);
		projection = glm::perspective(glm::radians(camera.getZoom()), width / (float)height, 0.1f, 100.0f);
		
		

		
		modelTest.use();
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		modelTest.setUniform("model", 1, GL_FALSE, glm::value_ptr(model));

		modelTest.setUniform("view", 1, GL_FALSE, glm::value_ptr(view));
		modelTest.setUniform("projection", 1, GL_FALSE, glm::value_ptr(projection));

		modelTest.setUniform("viewerPos", camera.getPosition());

		modelTest.setUniform("material.shininess", 255.0f);

		modelTest.setUniform("directionLight.direction", directionLight.direction);
		modelTest.setUniform("directionLight.ambient", directionLight.color);
		modelTest.setUniform("directionLight.diffuse", directionLight.color);
		modelTest.setUniform("directionLight.specular", directionLight.color);

		for (size_t i = 0; i < spotlights.size(); i++)
		{
			modelTest.setUniform("spotlights[" + std::to_string(i) + "].position", spotlights[i]->position);
			modelTest.setUniform("spotlights[" + std::to_string(i) + "].direction", spotlights[i]->direction);
			modelTest.setUniform("spotlights[" + std::to_string(i) + "].innerCutoff", (float)cos(glm::radians(spotlights[i]->innerCutoff)));
			modelTest.setUniform("spotlights[" + std::to_string(i) + "].outerCutoff", (float)cos(glm::radians(spotlights[i]->outerCutoff)));
			modelTest.setUniform("spotlights[" + std::to_string(i) + "].ambient", spotlights[i]->color / 10.0f);
			modelTest.setUniform("spotlights[" + std::to_string(i) + "].diffuse", spotlights[i]->color);
			modelTest.setUniform("spotlights[" + std::to_string(i) + "].specular", spotlights[i]->color);
			modelTest.setUniform("spotlights[" + std::to_string(i) + "].constant", spotlights[i]->intensityCoefs.x);
			modelTest.setUniform("spotlights[" + std::to_string(i) + "].linear", spotlights[i]->intensityCoefs.y);
			modelTest.setUniform("spotlights[" + std::to_string(i) + "].quadratic", spotlights[i]->intensityCoefs.z);
		}
		for (size_t i = 0; i < pointLights.size(); i++)
		{
			modelTest.setUniform("pointLights[" + std::to_string(i) + "].position", pointLights[i]->position);
			modelTest.setUniform("pointLights[" + std::to_string(i) + "].ambient", pointLights[i]->color);
			modelTest.setUniform("pointLights[" + std::to_string(i) + "].diffuse", pointLights[i]->color);
			modelTest.setUniform("pointLights[" + std::to_string(i) + "].specular", pointLights[i]->color);
			modelTest.setUniform("pointLights[" + std::to_string(i) + "].constant", pointLights[i]->intensityCoefs.x);
			modelTest.setUniform("pointLights[" + std::to_string(i) + "].linear", pointLights[i]->intensityCoefs.y);
			modelTest.setUniform("pointLights[" + std::to_string(i) + "].quadratic", pointLights[i]->intensityCoefs.z);
		}

		backpack.Draw(modelTest);
		
		glBindVertexArray(VAO1);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureLampPost);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-6.0f, 3.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f, 6.0f, 0.25));
		shaderCube.setUniform("model", 1, GL_FALSE, glm::value_ptr(model));

		shaderCube.setUniform("material.shininess", 255.0f);

		shaderCube.setUniform("material.diffuse", 0);
		shaderCube.setUniform("material.specular", 0);

		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-5.75f, 5.875f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25));
		shaderCube.setUniform("model", 1, GL_FALSE, glm::value_ptr(model));

		shaderCube.setUniform("material.shininess", 255.0f);

		glDrawArrays(GL_TRIANGLES, 0, 36);


		shaderLightSource.use();
		shaderLightSource.setUniform("view", 1, GL_FALSE, glm::value_ptr(view));
		shaderLightSource.setUniform("projection", 1, GL_FALSE, glm::value_ptr(projection));


		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 50.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f));

		shaderLightSource.setUniform("model", 1, GL_FALSE, glm::value_ptr(model));

		shaderLightSource.setUniform("lightColor", directionLight.color);

		//glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		for (size_t i = 0; i < pointLights.size(); i++)
		{
			model = glm::mat4(1.0f);
			model = glm::translate(model, pointLights[i]->position);
			model = glm::scale(model, glm::vec3(0.2f));

			shaderLightSource.setUniform("model", 1, GL_FALSE, glm::value_ptr(model));

			shaderLightSource.setUniform("lightColor", pointLights[i]->color);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		for (size_t i = 0; i < spotlights.size(); i++)
		{
			model = glm::mat4(1.0f);
			model = glm::translate(model, spotlights[i]->position);
			model = glm::scale(model, glm::vec3(0.2f));

			shaderLightSource.setUniform("model", 1, GL_FALSE, glm::value_ptr(model));

			shaderLightSource.setUniform("lightColor", spotlights[i]->color);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	glfwTerminate();
	return 0;
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	::width = width;
	::height = height;
}
void mouse_callback(GLFWwindow* window, double xPos, double yPos)
{
	if (firstMouse == true)
	{
		lastX = static_cast<float>(xPos);
		lastY = static_cast<float>(yPos);
		firstMouse = false;
	}
	float xOffset = (float)xPos - lastX;
	float yOffset = lastY - (float)yPos;
	lastX = static_cast<float>(xPos);
	lastY = static_cast<float>(yPos);
	camera.processMouseMovement(xOffset, yOffset, true);
}
void scroll_callback(GLFWwindow* window, double xOffset, double yOffset)
{
	camera.processMouseScroll(static_cast<float>(yOffset));
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) != GLFW_PRESS)
		return;
	else if (key == GLFW_KEY_TAB && action == GLFW_PRESS)
	{
		if (selectedPointLight == pointLights.size() - 1)
			selectedPointLight = 0;
		else
			selectedPointLight++;
		camera.lookAlongVector(pointLights[selectedPointLight]->getDirectionVector(camera.getPosition()));
	}
}
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		mixVal += 0.001f;
		if (mixVal > 1.0f)
			mixVal = 1.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		mixVal -= 0.001f;
		if (mixVal < 0.0f)
			mixVal = 0.0f;
	}
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS)
	{
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			pointLights[selectedPointLight]->position.z -= deltaTime * 4.0f;
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			pointLights[selectedPointLight]->position.z += deltaTime * 4.0f;
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			pointLights[selectedPointLight]->position.x -= deltaTime * 4.0f;
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			pointLights[selectedPointLight]->position.x += deltaTime * 4.0f;
		}
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			pointLights[selectedPointLight]->position.y += deltaTime * 4.0f;
		}
		if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		{
			pointLights[selectedPointLight]->position.y -= deltaTime * 4.0f;
		}

		if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
		{
			pointLights[selectedPointLight]->color.r += deltaTime * 1.0f;
			if (pointLights[selectedPointLight]->color.r > 1.0f)
				pointLights[selectedPointLight]->color.r = 1.0f;
		}
		if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
		{
			pointLights[selectedPointLight]->color.r -= deltaTime * 1.0f;
			if (pointLights[selectedPointLight]->color.r < 0.0f)
				pointLights[selectedPointLight]->color.r = 0.0f;
		}
		if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
		{
			pointLights[selectedPointLight]->color.g += deltaTime * 1.0f;
			if (pointLights[selectedPointLight]->color.g > 1.0f)
				pointLights[selectedPointLight]->color.g = 1.0f;
		}
		if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
		{
			pointLights[selectedPointLight]->color.g -= deltaTime * 1.0f;
			if (pointLights[selectedPointLight]->color.g < 0.0f)
				pointLights[selectedPointLight]->color.g = 0.0f;
		}
		if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
		{
			pointLights[selectedPointLight]->color.b += deltaTime * 1.0f;
			if (pointLights[selectedPointLight]->color.b > 1.0f)
				pointLights[selectedPointLight]->color.b = 1.0f;
		}
		if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
		{
			pointLights[selectedPointLight]->color.b -= deltaTime * 1.0f;
			if (pointLights[selectedPointLight]->color.b < 0.0f)
				pointLights[selectedPointLight]->color.b = 0.0f;
		}
		return;
	}
	else
	{
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			camera.processKeyboard(FORWARD, deltaTime);
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			camera.processKeyboard(BACKWARD, deltaTime);
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			camera.processKeyboard(LEFT, deltaTime);
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			camera.processKeyboard(RIGHT, deltaTime);
		}
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			camera.processKeyboard(UP, deltaTime);
		}
		if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		{
			camera.processKeyboard(DOWN, deltaTime);
		}
	}
}