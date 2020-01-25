#include "CameraController.h"
#include "Inputs/Input.h"
#include <functional>
// TODO: Get rid of GLFW include
#include "GLFW/glfw3.h"

namespace GLCore {

#define BIND_EVENT_FN(x) std::bind(&CameraController::x, this, std::placeholders::_1)

	// TODO: Add aspect ratio as a parameter in the constructor
	CameraController::CameraController()
		: m_HorizontalAngle(3.14f), m_VerticalAngle(0.0f), m_InitialFoV(45.0f), m_Speed(3.0f),
		m_MouseSpeed(0.05f), m_CameraPosition(glm::vec3(4.0f, 3.0f, 3.0f)),
		m_CameraDirection(glm::vec3(-4.0f, -3.0f, -3.0f)), m_CameraUp(glm::vec3(0.0f, 1.0f, 0.0f)),
		m_ViewMatrix(glm::mat4(1.0f)), m_ProjectionMatrix(glm::mat4(1.0f)), m_FOV(45.0f)
	{
		m_WindowWidth = 1280.0f;
		m_WindowHeight = 720.0f;
		m_AspectRatio = m_WindowWidth / m_WindowHeight;
		m_ProjectionMatrix = glm::perspective(glm::radians(45.0f), m_AspectRatio, 0.1f, 100.0f);
		m_ViewMatrix = glm::lookAt(m_CameraPosition, m_CameraPosition + m_CameraDirection, m_CameraUp);
	}

	CameraController::~CameraController()
	{
	}

	void CameraController::OnUpdate(float deltaTime)
	{
		// Get mouse position
		std::pair<float,float> mousePosition = Input::GetMousePosition();
		float xpos = mousePosition.first;
		float ypos = mousePosition.second;
		// Reset mouse position for next frame
		Input::SetMousePosition(m_WindowWidth / 2.0f, m_WindowHeight / 2.0f);

		// Compute new orientation
		m_HorizontalAngle += m_MouseSpeed * deltaTime * float(m_WindowWidth / 2 - xpos);
		m_VerticalAngle += m_MouseSpeed * deltaTime * float(m_WindowHeight / 2 - ypos);

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


		if (Input::IsKeyPressed(GLFW_KEY_UP))
		{
			m_CameraPosition += m_CameraDirection * deltaTime * m_Speed;
		}
		else if (Input::IsKeyPressed(GLFW_KEY_DOWN))
		{
			m_CameraPosition -= m_CameraDirection * deltaTime * m_Speed;
		}

		if (Input::IsKeyPressed(GLFW_KEY_RIGHT))
		{
			m_CameraPosition += right * deltaTime * m_Speed;
		}
		else if (Input::IsKeyPressed(GLFW_KEY_LEFT))
		{
			m_CameraPosition -= right * deltaTime * m_Speed;
		}


		m_ProjectionMatrix = glm::perspective(glm::radians(m_FOV), m_AspectRatio, 0.1f, 100.0f);
		m_ViewMatrix = glm::lookAt(
			m_CameraPosition,				      // Camera is at (4,3,3), in World Space
			m_CameraPosition + m_CameraDirection, // and looks at the origin
			m_CameraUp					          // Head is up (set to 0,-1,0 to look upside-down)
		);
		
	}

	void CameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT_FN(OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OnWindowResized));
	}

	bool CameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		m_FOV -= 5 * e.GetYOffset();
		return false;
	}

	bool CameraController::OnWindowResized(WindowResizeEvent& e)
	{
		m_WindowHeight = (float)e.GetHeight();
		m_WindowWidth = (float)e.GetWidth();
		m_AspectRatio = m_WindowWidth / m_WindowHeight;
		m_ProjectionMatrix = glm::perspective(glm::radians(m_FOV), m_AspectRatio, 0.1f, 100.0f);
		return false;
	}



}


