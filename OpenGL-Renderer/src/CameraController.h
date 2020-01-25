#pragma once
#include "Controller.h"
#include "Events/Event.h"
#include "Events/MouseEvent.h"
#include "Events/ApplicationEvent.h"

namespace GLCore 
{

	class CameraController : public Controller
	{
	public:
		CameraController();
		~CameraController();

		//void ComputeNewState(float deltaTime);
		void OnUpdate(float deltaTime);
		void OnEvent(Event& e);
		bool OnMouseScrolled(MouseScrolledEvent& e);
		//bool OnMouseMoved(MouseMovedEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
		glm::vec3 GetPosition() const { return m_CameraPosition; }
		glm::vec3 GetDirection() const { return m_CameraDirection; }
		glm::vec3 GetUpVector() const { return m_CameraUp; }
		glm::mat4 GetViewMatrix() const { return m_ViewMatrix; }
		glm::mat4 GetProjectionMatrix() const { return m_ProjectionMatrix; }
		float GetFOV() const { return m_FOV; }

	private:

		glm::vec3 m_CameraPosition;
		glm::vec3 m_CameraDirection;
		glm::vec3 m_CameraUp;

		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ProjectionMatrix;
		
		float m_AspectRatio;
		float m_WindowWidth;
		float m_WindowHeight;
		float m_HorizontalAngle;
		float m_VerticalAngle;
		float m_InitialFoV;
		float m_Speed;
		float m_MouseSpeed;
		float m_FOV;
	};
}