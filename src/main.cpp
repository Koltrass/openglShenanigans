#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "Shader.h"
#include "Camera.h"

float mixVal = 0.5f;
int width = 800;
int height = 600;

Camera camera(0.0f, 0.0f, 3.0f, 0.0f, 1.0f, 0.0f, -90.0f, 0.0f);
float deltaTime = 0.0f;
float lastFrame = 0.0f;

float lastX = width/ 2.0f;
float lastY = height / 2.0f;
bool firstMouse = true;

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
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}
	float xOffset = (float)xPos - lastX;
	float yOffset = lastY - (float)yPos;
	lastX = xPos;
	lastY = yPos;
	camera.processMouseMovement(xOffset, yOffset, true);
}
void scroll_callback(GLFWwindow* window, double xOffset, double yOffset)
{
	camera.processMouseScroll(yOffset);
}
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		mixVal += 0.001;
		if (mixVal > 1.0f)
			mixVal = 1.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		mixVal -= 0.001;
		if (mixVal < 0.0f)
			mixVal = 0.0f;
	}
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

int main()
{
	float triangle4[] = { -0.5f,  0.5f,  0.0f,   1.0f, 0.0f, 0.0f,   0.0f,  1.0f,
						  -0.5f, -0.5f,  0.0f,   0.0f, 1.0f, 0.0f,   0.0f,  0.0f,
						   0.5f, -0.5f,  0.0f,   0.0f, 0.0f, 1.0f,   1.00f, 0.0f,
						   0.5f,  0.5f,  0.0f,   1.0f, 1.0f, 0.0f,   1.00f, 1.0f,
						  -0.5f,  0.5f,  1.0f,   1.0f, 1.0f, 0.0f,   0.0f,  1.0f,
						  -0.5f, -0.5f,  1.0f,   0.0f, 1.0f, 1.0f,   0.0f,  0.0f,
						   0.5f, -0.5f,  1.0f,   1.0f, 0.0f, 1.0f,   1.00f, 0.0f,
						   0.5f,  0.5f,  1.0f,   1.0f, 1.0f, 1.0f,   1.00f, 1.0f, };
	unsigned int indices[] = { 0, 1, 2, 0, 2, 3, 1, 5, 2, 5, 2, 6, 5, 6, 7, 5, 4, 7, 0, 4, 3, 4, 3, 7, 2, 3, 7, 2, 6, 7, 0, 4, 5, 0, 1, 5 };

	glm::vec3 cubePositions[] =
	{
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(-1.3f,  1.0f, -1.5f),
		glm::vec3( 0.0f,  0.0f,  0.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3( 2.4f, -0.4f, -3.5f),
		glm::vec3( 2.0f,  5.0f, -15.0f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3( 1.3f, -2.0f, -2.5f),
		glm::vec3( 1.5f,  2.0f, -2.5f),
		glm::vec3( 1.5f,  0.2f, -1.5f)
	};

	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(width, height, "Small window", NULL, NULL);
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

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	unsigned int VAO4;
	glGenVertexArrays(1, &VAO4);
	glBindVertexArray(VAO4);

	unsigned int VBO4;
	glGenBuffers(1, &VBO4);
	glBindBuffer(GL_ARRAY_BUFFER, VBO4);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle4), triangle4, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(sizeof(float)*3));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(sizeof(float)*6));
	glEnableVertexAttribArray(2);

	unsigned int EBO4;
	glGenBuffers(1, &EBO4);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO4);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	Shader shader4("Shaders/Vertex/textured.vert", "Shaders/Fragment/textured.frag");

	unsigned int texture1, texture2;
	glGenTextures(1, &texture1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	int textureWidth, textureHeight, nOfChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load("Textures/brickWall.jpg", &textureWidth, &textureHeight, &nOfChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "ERROR::TEXTURE::FAILED_TO_LOAD\n";
	}
	stbi_image_free(data);

	glGenTextures(1, &texture2);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	data = stbi_load("Textures/knight.jpg", &textureWidth, &textureHeight, &nOfChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "ERROR::TEXTURE::FAILED_TO_LOAD\n";
	}
	stbi_image_free(data);

	shader4.use();
	shader4.setUniform("myTexture1", 0);
	shader4.setUniform("myTexture2", 1);

	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window);


		glClearColor(0.1f, 0.0f, 0.15f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glBindVertexArray(VAO4);
		shader4.use();
		shader4.setUniform("mixVal", mixVal);
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.5f, -0.5f, 0.0f));
		model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -0.5f));
		
		glm::mat4 view = glm::mat4(1.0f);
		view = camera.getViewMatrix();

		glm::mat4 projection = glm::mat4(1.0f);
		//projection = glm::ortho(-(float)width/height, (float)width/height, -1.0f, 1.0f, 0.1f, 100.0f);
		projection = glm::perspective(glm::radians(camera.getZoom()), width / (float)height, 0.1f, 100.0f);

		shader4.setUniform("model", 1, GL_FALSE, glm::value_ptr(model));
		shader4.setUniform("view", 1, GL_FALSE, glm::value_ptr(view));
		shader4.setUniform("projection", 1, GL_FALSE, glm::value_ptr(projection));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.5f, 0.5f, 0.0f));
		model = glm::scale(model, glm::vec3(sin((float)glfwGetTime()), sin((float)glfwGetTime()), sin((float)glfwGetTime())));
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -0.5f));

		shader4.setUniform("model", 1, GL_FALSE, glm::value_ptr(model));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		for (int i = 0; i < std::size(cubePositions); i++)
		{
			model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = 0;
			if (i % 3 == 0)  // every 3rd iteration (including the first) we set the angle using GLFW's time function.
				angle = glfwGetTime() * 25.0f;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			shader4.setUniform("model", 1, GL_FALSE, glm::value_ptr(model));
			model = glm::scale(model, glm::vec3(sin((float)glfwGetTime()), sin((float)glfwGetTime()), sin((float)glfwGetTime())));
			glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		}



		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	glfwTerminate();
	return 0;
}