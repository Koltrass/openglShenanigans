#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <iostream>

#include "Shader.h"
void framebuffer_size_callback(GLFWwindow*, int width, int height)
{
	glViewport(0, 0, width, height);
}
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}
int main()
{
	int width = 800;
	int height = 600;
	float triangle1[] = { -0.9f, -0.9f, 0.0f, 0.1f,
						  -0.9f,  0.4f, 0.0f, 0.4f,
						  -0.2f, -0.9f, 0.0f, 0.8f};
	float triangle2[] = {  0.9f,  0.9f, 0.0f,
						   0.9f, -0.4f, 0.0f,
						   0.2f,  0.9f, 0.0f };
	float triangle3[] = {  0.0f,  0.9f, 0.0f,
					      -0.5f, -0.4f, 0.0f,
					       0.5f,  0.0f, 0.0f };
	unsigned int indices[] = { 0, 1, 2, 3, 4, 5 };

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

	unsigned int VAO1;
	glGenVertexArrays(1, &VAO1);
	glBindVertexArray(VAO1);

	unsigned int VBO1;
	glGenBuffers(1, &VBO1);
	glBindBuffer(GL_ARRAY_BUFFER, VBO1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle1), triangle1, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	unsigned VAO2;
	glGenVertexArrays(1, &VAO2);
	glBindVertexArray(VAO2);

	unsigned int VBO2;
	glGenBuffers(1, &VBO2);
	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle2), triangle2, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	unsigned int VAO3;
	glGenVertexArrays(1, &VAO3);
	glBindVertexArray(VAO3);

	unsigned int VBO3;
	glGenBuffers(1, &VBO3);
	glBindBuffer(GL_ARRAY_BUFFER, VBO3);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle3), triangle3, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	Shader shader1("Shaders/Vertex/vertex1.vert", "Shaders/Fragment/fragment1.frag");
	Shader shader2("Shaders/Vertex/vertex1.vert", "Shaders/Fragment/fragment2.frag");
	Shader shader3("Shaders/Vertex/vertex2.vert", "Shaders/Fragment/fragment3.frag");

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.1f, 0.0f, 0.15f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(VAO1);
		shader1.use();
		shader1.setUniform("offsetX", 1.1f);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindVertexArray(VAO2);
		shader2.use();
		float time = glfwGetTime();
		float redValue = (sin(time) + 1.0f) / 2.0f;
		float greenValue = (cos(time) + 1.0f) / 2.0f;
		shader2.setUniform("changingColor", redValue, greenValue);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindVertexArray(VAO3);
		shader3.use();
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	glfwTerminate();
	return 0;
}