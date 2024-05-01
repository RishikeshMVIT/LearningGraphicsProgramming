#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>


class Camera
{

public:
	glm::vec3 position;
	glm::vec3 orientation = glm::vec3(0.0f,  0.0f, -1.0f);
	glm::vec3 upDirection = glm::vec3(0.0f,  1.0f,  0.0f);

	int width;
	int height;
	float speed		  = 0.1f;
	float swnsitivity = 0.1f;
};

