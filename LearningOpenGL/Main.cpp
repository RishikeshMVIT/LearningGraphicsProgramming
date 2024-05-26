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

//Pyramid
GLfloat vertices[] =
{  //COORDINATES            COLORS                   TexCoord         NORMALS
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 5.0f,      0.0f, -1.0f, 0.0f, // Bottom side
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 5.0f,      0.0f, -1.0f, 0.0f, // Bottom side
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side

	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // Left Side
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // Left Side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,     -0.8f, 0.5f,  0.0f, // Left Side

	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.0f, 0.5f, -0.8f, // Non-facing side

	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      0.8f, 0.5f,  0.0f, // Right side
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.8f, 0.5f,  0.0f, // Right side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.8f, 0.5f,  0.0f, // Right side

	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, 0.5f,  0.8f, // Facing side
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, 0.5f,  0.8f, // Facing side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.0f, 0.5f,  0.8f  // Facing side
};

GLuint indices[] =
{
	0, 1, 2, // Bottom side
	0, 2, 3, // Bottom side
	4, 6, 5, // Left side
	7, 9, 8, // Non-facing side
	10, 12, 11, // Right side
	13, 15, 14 // Facing side
};

//Plane
//GLfloat vertices[] =
//{
//	-1.0f,  0.0f,  1.0f,	0.0f, 0.0f, 0.0f,	 0.0f, 0.0f,	0.0f, 1.0f, 0.0f,
//	-1.0f,  0.0f, -1.0f,	0.0f, 0.0f, 0.0f,	 0.0f, 1.0f,	0.0f, 1.0f, 0.0f,
//	 1.0f,  0.0f, -1.0f,	0.0f, 0.0f, 0.0f,	 1.0f, 1.0f,	0.0f, 1.0f, 0.0f,
//	 1.0f,  0.0f,  1.0f,	0.0f, 0.0f, 0.0f,	 1.0f, 0.0f,	0.0f, 1.0f, 0.0f
//};
//
//GLuint indices[] =
//{
//	0, 1, 2,
//	0, 2, 3
//};

GLfloat lightVertices[] =
{ //     COORDINATES     //
	-0.1f, -0.1f,  0.1f,
	-0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f,  0.1f,
	-0.1f,  0.1f,  0.1f,
	-0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f,  0.1f
};

GLuint lightIndices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7
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

	//Vertex Attribute Object
	VAO vao;
	vao.Bind();

	//Vertex Buffer Object
	VBO vbo(vertices, sizeof(vertices));
	//Entity Buffer Object
	EBO ebo(indices,  sizeof(indices));

	vao.LinkAttributes(vbo, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)(0));
	vao.LinkAttributes(vbo, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	vao.LinkAttributes(vbo, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	vao.LinkAttributes(vbo, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));

	vao.Unbind();
	vbo.Unbind();
	ebo.Unbind();
	
	VAO lightVAO;
	lightVAO.Bind();
	
	VBO lightVBO(lightVertices, sizeof(lightVertices));
	EBO lightEBO(lightIndices, sizeof(lightIndices));

	lightVAO.LinkAttributes(lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);

	lightVAO.Unbind();
	lightVBO.Unbind();
	lightEBO.Unbind();

	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPosition = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPosition);

	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, position);

	//Shaders
	Shader basicShader("D:/Projects/LearningGraphicsProgramming/LearningOpenGL/Resources/Shader/BasicShader.vert", "D:/Projects/LearningGraphicsProgramming/LearningOpenGL/Resources/Shader/BasicShader.frag");

	Shader lightShader("D:/Projects/LearningGraphicsProgramming/LearningOpenGL/Resources/Shader/Emissive.vert", "D:/Projects/LearningGraphicsProgramming/LearningOpenGL/Resources/Shader/Emissive.frag");

	lightShader.Use();
	glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);

	basicShader.Use();
	glUniformMatrix4fv(glGetUniformLocation(basicShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
	glUniform4f(glGetUniformLocation(basicShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(basicShader.ID, "lightPosition"), lightPosition.x, lightPosition.y, lightPosition.z);

	//Texture
	Texture demoTexture("D:/Projects/LearningGraphicsProgramming/LearningOpenGL/Resources/Textures/Stone_Albedo.jpg", GL_TEXTURE_2D, 0, GL_RGB, GL_UNSIGNED_BYTE);
	demoTexture.AssignTextureUnit(basicShader, "albedoTex", 0);
	Texture specularMap("D:/Projects/LearningGraphicsProgramming/LearningOpenGL/Resources/Textures/Stone_Specular.jpg", GL_TEXTURE_2D, 1, GL_RED, GL_UNSIGNED_BYTE);
	specularMap.AssignTextureUnit(basicShader, "specularMap", 1);

	glEnable(GL_DEPTH_TEST);

	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	//Main Loop
	while (!glfwWindowShouldClose(window))
	{
		//Input Processing
		OnInput(window);
		camera.OnInput(window);

		//Rendering Commands
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.UpdateMatrix(45.0f, 0.1f, 100.0f);

		basicShader.Use();
		glUniform3f(glGetUniformLocation(basicShader.ID, "cameraPosition"), camera.position.x, camera.position.y, camera.position.z);
		camera.SetMatrix(basicShader, "CAMERA_MATRIX");
		demoTexture.Bind();
		specularMap.Bind();
		vao.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(vertices) / sizeof(int), GL_UNSIGNED_INT, 0);


		lightShader.Use();
		camera.SetMatrix(lightShader, "CAMERA_MATRIX");
		lightVAO.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int), GL_UNSIGNED_INT, 0);

		//Swap Buffers
		glfwSwapBuffers(window);

		//Check and Call events
		glfwPollEvents();
	}

	vao.Delete();
	vbo.Delete();
	ebo.Delete();
	lightVAO.Delete();
	lightVBO.Delete();
	lightEBO.Delete();
	demoTexture.Delete();
	basicShader.Delete();
	lightShader.Delete();

	glfwDestroyWindow(window);

	glfwTerminate();

	return 0;
}
