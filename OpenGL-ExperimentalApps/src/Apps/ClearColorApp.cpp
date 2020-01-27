#include "ClearColorApp.h"
#include "Renderer.h"
#include "imgui/imgui.h"

ExperimentalApps::ClearColorLayer::ClearColorLayer()
	:m_ClearColor{0.2f, 0.2f, 0.8f, 1.0f}
{
}

ExperimentalApps::ClearColorLayer::~ClearColorLayer()
{
}

void ExperimentalApps::ClearColorLayer::OnAttach()
{
}

void ExperimentalApps::ClearColorLayer::OnDetach()
{
}

void ExperimentalApps::ClearColorLayer::OnUpdate(float deltaTime)
{
	OnRender();
}

void ExperimentalApps::ClearColorLayer::OnRender()
{
	GLCall(glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]));
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void ExperimentalApps::ClearColorLayer::OnImGuiRender()
{
	ImGui::ColorEdit4("Clear Color", m_ClearColor);
}
