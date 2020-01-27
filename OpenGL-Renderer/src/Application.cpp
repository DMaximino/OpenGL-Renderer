#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Window/Window.h"
#include "Application.h"


namespace GLCore {

// This creates a bound funtion that will run the function x taking as parameters 'this' and the first argument of the function x (_1)
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)


	Application* Application::s_Instance = nullptr;

	Application::Application(const std::string& name, uint32_t width, uint32_t height)
	{
		if (!s_Instance)
		{
			// Initialize core
			//Log::Init();
		}

		//GLCORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create({ name, width, height }));
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		// Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
	}

	// Function that is bound to the callback function of window
	void Application::OnEvent(Event& e)
	{
		// Creates a dispatcher that takes the received event in the constructor
		EventDispatcher dispatcher(e);
		// Verifies the the received event belongs to a certain type of event
		// if so the event is dispatched to the right function to handle events 
		// of this type and the evend is marked as 'handled'
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::Run()
	{
		double lastTime = glfwGetTime();
		while (m_Running)
		{
			double deltaTime = float(glfwGetTime() - lastTime);
			lastTime = glfwGetTime();

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate(deltaTime);

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	// The method that is called by the dispatcher when a event of the 
	// type WindowCloseEvent is triggered
	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

}

//
//void main() {
//
//}
