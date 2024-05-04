//Defines

//Runtimes
#include <iostream>

//Libraries
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <stb\stb_image.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

//Includes
#include "Shader.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Texture.h"
#include "Camera.h"

//TODO: Refactor to own class
void OnFramebufferResize(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void OnInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	
}

//Window width and height
const unsigned int width = 960;
const unsigned int height = 960;

//Vertex Input
GLfloat vertices[] = {
	//Positions           //Color				 //TexCoords
	-0.5f, 0.0f,  0.5f,   0.83f, 0.70f, 0.44f,   0.0f, 0.0f,
	-0.5f, 0.0f, -0.5f,   0.83f, 0.70f, 0.44f,   1.0f, 0.0f,
	 0.5f, 0.0f, -0.5f,   0.83f, 0.70f, 0.44f,   0.0f, 0.0f,
	 0.5f, 0.0f,  0.5f,   0.83f, 0.70f, 0.44f,   1.0f, 0.0f,
	 0.0f, 0.8f,  0.0f,   0.92f, 0.86f, 0.76f,   0.5f, 1.0f
};

GLuint indices[] = {
	0,1,2,
	0,2,3,
	0,1,4,
	1,2,4,
	2,3,4,
	3,0,4
};

int main()
{
	//GLFW Intitialisation
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//Create Window
	GLFWwindow* window = glfwCreateWindow(width, height, "LearningOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	//Setting GLFW Context
	glfwMakeContextCurrent(window);

	//Initializing OpenGL
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize OpenGL" << std::endl;
		return -1;
	}

	//Setting Viewport Dimensions
	glViewport(0, 0, width, height);
	glfwSetFramebufferSizeCallback(window, OnFramebufferResize);

	//Shaders
	Shader basicShader("D:/Projects/LearningGraphicsProgramming/LearningOpenGL/Resources/Shader/BasicShader.vert", "D:/Projects/LearningGraphicsProgramming/LearningOpenGL/Resources/Shader/BasicShader.frag");

	//Vertex Attribute Object
	VAO vao;
	vao.Bind();

	//Vertex Buffer Object
	VBO vbo(vertices, sizeof(vertices));
	//Entity Buffer Object
	EBO ebo(indices,  sizeof(indices));

	vao.LinkAttributes(vbo, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)(0));
	vao.LinkAttributes(vbo, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	vao.LinkAttributes(vbo, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	vao.Unbind();
	vbo.Unbind();
	ebo.Unbind();

	//Texture
	Texture demoTexture("D:/Projects/LearningGraphicsProgramming/LearningOpenGL/Resources/Textures/UVChecker.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	demoTexture.AssignTextureUnit(basicShader, "inTexture", 0);

	glEnable(GL_DEPTH_TEST);

	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	//Main Loop
	while (!glfwWindowShouldClose(window))
	{
		//Input Processing
		OnInput(window);
		camera.OnInput(window);

		//Rendering Commands
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		basicShader.Use();

		camera.SetMatrix(45.0f, 0.1f, 100.0f, basicShader, "CAMERA_MATRIX");

		demoTexture.Bind();
		vao.Bind();

		//Draw Primitives
		glDrawElements(GL_TRIANGLES, sizeof(vertices)/sizeof(int), GL_UNSIGNED_INT, 0);

		//Swap Buffers
		glfwSwapBuffers(window);

		//Check and Call events
		glfwPollEvents();
	}

	vao.Delete();
	vbo.Delete();
	ebo.Delete();
	demoTexture.Delete();
	basicShader.Delete();

	glfwTerminate();

	return 0;
}
