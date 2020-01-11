#include "CameraController.h"


	// Global variable for mouse scroll wheel callback
	double fov = 45.0f;

	void ScrollCallback(GLFWwindow* window, double wheelPositionX, double whellPositionY)
	{
		fov -= 5 * whellPositionY;
	}

	CameraController::CameraController(WindowProperties windowProperties)
		: m_HorizontalAngle(3.14f), m_VerticalAngle(0.0f), m_InitialFoV(45.0f), m_Speed(3.0f),
		m_MouseSpeed(0.05f), m_Window(windowProperties), m_CameraPosition(glm::vec3(4.0f, 3.0f, 3.0f)),
		m_CameraDirection(glm::vec3(-4.0f, -3.0f, -3.0f)), m_CameraUp(glm::vec3(0.0f, 1.0f, 0.0f)),
		m_ViewMatrix(glm::mat4(1.0f)), m_ProjectionMatrix(glm::mat4(1.0f)), m_FOV(45.0f)
	{
		m_ProjectionMatrix = glm::perspective(glm::radians(45.0f), m_Window.Width / m_Window.Height, 0.1f, 100.0f);
		m_ViewMatrix = glm::lookAt(m_CameraPosition, m_CameraPosition + m_CameraDirection, m_CameraUp);
		glfwSetScrollCallback(m_Window.WindowObject, ScrollCallback);
	}

	CameraController::~CameraController()
	{
	}

	void CameraController::ComputeNewState(float deltaTime)
	{
		// Get mouse position
		double xpos, ypos;
		glfwGetCursorPos(m_Window.WindowObject, &xpos, &ypos);
		// Reset mouse position for next frame
		glfwSetCursorPos(m_Window.WindowObject, m_Window.Width / 2.0f, m_Window.Height / 2.0f);

		// Compute new orientation
		m_HorizontalAngle += m_MouseSpeed * deltaTime * float(960.0f / 2 - xpos);
		m_VerticalAngle += m_MouseSpeed * deltaTime * float(540.0f / 2 - ypos);

		m_CameraDirection = glm::vec3(
			cos(m_VerticalAngle) * sin(m_HorizontalAngle),
			sin(m_VerticalAngle),
			cos(m_VerticalAngle) * cos(m_HorizontalAngle)
		);

		glm::vec3 right = glm::vec3(
			sin(m_HorizontalAngle - 3.14f / 2.0f),
			0,
			cos(m_HorizontalAngle - 3.14f / 2.0f)
		);

		// Up vector : perpendicular to both direction and right
		m_CameraUp = glm::cross(right, m_CameraDirection);

		// Move forward
		if (glfwGetKey(m_Window.WindowObject, GLFW_KEY_UP) == GLFW_PRESS) {
			m_CameraPosition += m_CameraDirection * deltaTime * m_Speed;
		}
		// Move backward
		if (glfwGetKey(m_Window.WindowObject, GLFW_KEY_DOWN) == GLFW_PRESS) {
			m_CameraPosition -= m_CameraDirection * deltaTime * m_Speed;
		}
		// Strafe right
		if (glfwGetKey(m_Window.WindowObject, GLFW_KEY_RIGHT) == GLFW_PRESS) {
			m_CameraPosition += right * deltaTime * m_Speed;
		}
		// Strafe left
		if (glfwGetKey(m_Window.WindowObject, GLFW_KEY_LEFT) == GLFW_PRESS) {
			m_CameraPosition -= right * deltaTime * m_Speed;
		}

		// Field of view
		m_FOV = fov;

		m_ProjectionMatrix = glm::perspective(glm::radians(m_FOV), m_Window.Width / m_Window.Height, 0.1f, 100.0f);
		m_ViewMatrix = glm::lookAt(
			m_CameraPosition,				      // Camera is at (4,3,3), in World Space
			m_CameraPosition + m_CameraDirection, // and looks at the origin
			m_CameraUp					          // Head is up (set to 0,-1,0 to look upside-down)
		);
	}



