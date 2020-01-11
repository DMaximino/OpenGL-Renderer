#pragma once
#include "Controller.h"

class CameraController : public Controller
{
public:
	CameraController(WindowProperties window);
	~CameraController();

	void ComputeNewState(float deltaTime);
	glm::vec3 GetPosition() const {	return m_CameraPosition; }
	glm::vec3 GetDirection() const { return m_CameraDirection; }
	glm::vec3 GetUpVector() const { return m_CameraUp; } 
	glm::mat4 GetViewMatrix() const { return m_ViewMatrix; }
	glm::mat4 GetProjectionMatrix() const { return m_ProjectionMatrix; }
	float GetFOV() const { return m_FOV; }

private:
	WindowProperties m_Window;

	glm::vec3 m_CameraPosition;
	glm::vec3 m_CameraDirection;
	glm::vec3 m_CameraUp;

	glm::mat4 m_ViewMatrix;
	glm::mat4 m_ProjectionMatrix;

	float m_HorizontalAngle; 
	float m_VerticalAngle;   
	float m_InitialFoV;
	float m_Speed;			 
	float m_MouseSpeed;
	float m_FOV;
};