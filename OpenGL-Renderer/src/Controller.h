#pragma once
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

struct WindowProperties
{
	GLFWwindow* WindowObject;
	float Width;
	float Height;
};

class Controller
{
public:
	Controller() {}
	virtual ~Controller() {}

	//virtual glm::vec3 GetPosition() = 0;
	//virtual glm::vec3 GetDirection() = 0;
};