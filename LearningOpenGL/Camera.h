#pragma once

#define GLM_ENABLE_EXPERIMENTAL

#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtx\rotate_vector.hpp>
#include <glm\gtx\vector_angle.hpp>

#include "Shader.h"

class Camera
{
public:
	Camera(int width, int height, glm::vec3 position) : width(width), height(height), position(position) {};

	void UpdateMatrix(float fow, float nearPlane, float farPlane);
	void SetMatrix(Shader& shader, const char* uniform);
	void OnInput(GLFWwindow* window);

public:
	glm::vec3 position;
	glm::vec3 orientation = glm::vec3(0.0f,  0.0f, -1.0f);
	glm::vec3 up = glm::vec3(0.0f,  1.0f,  0.0f);

	glm::mat4 matrix = glm::mat4(1.0f);

	int width;
	int height;

	float speed		  = 0.1f;
	float sensitivity = 2.0f;

	bool firstClick = true;
};

