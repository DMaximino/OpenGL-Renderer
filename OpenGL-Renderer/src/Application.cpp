#include <GL/glew.h>
//#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "Texture.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "Window/Window.h"

#include "tests/TestClearColor.h"
#include "tests/TestTexture2D.h"
#include "tests/TestDrawCube.h"
#include "tests/TestDrawMultipleObjects.h"
#include "tests/Test.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
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
		// When setting the event callback we are passing a function that is bound to the function we want to call on our side when the event is sent
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		GLFWwindow* native_window = static_cast<GLFWwindow*>(m_Window->GetNativeWindow());
		const char* glsl_version = "#version 130";

		// Renderer::Init();

		//m_ImGuiLayer = new ImGuiLayer();
		//PushOverlay(m_ImGuiLayer);

		// Setup Dear ImGui context
		ImGui::CreateContext();

		ImGui::StyleColorsDark();
		ImGui_ImplGlfw_InitForOpenGL(native_window, true);
		ImGui_ImplOpenGL3_Init(glsl_version);

		//windowProperties = { native_window,(float) m_Window->GetWidth(), (float) m_Window->GetHeight() };

		m_CurrentTest = nullptr;
		m_TestMenu = new test::TestMenu(m_CurrentTest);
		m_CurrentTest = m_TestMenu;

		m_TestMenu->RegisterTest<test::TestClearColor>("Clear Color");
		m_TestMenu->RegisterTest<test::TestTexture2D>("Texture 2D");
		m_TestMenu->RegisterTest<test::TestDrawCube>("Draw Cube");
		m_TestMenu->RegisterTest<test::TestDrawMultipleObjects>("Draw Multiple Objects");
	}

	Application::~Application() 
	{
		delete m_CurrentTest;
		if (m_CurrentTest != m_TestMenu)
			delete m_TestMenu;
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

		m_CurrentTest->OnEvent(e);

	/*	for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}*/
	}

	void Application::Run()
	{
		Renderer renderer;
		double lastTime = glfwGetTime();
		while (m_Running)
		{
			GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));

			/* Render here */
			renderer.Clear();

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			if (m_CurrentTest)
			{
				double deltaTime = float(glfwGetTime() - lastTime);
				m_CurrentTest->OnUpdate(deltaTime);
				lastTime = glfwGetTime();
				m_CurrentTest->OnRender();
				ImGui::Begin("Test");
				if (m_CurrentTest != m_TestMenu && ImGui::Button("<-"))
				{
					delete m_CurrentTest;
					m_CurrentTest = m_TestMenu;
				}
				m_CurrentTest->OnImGuiRender();
				ImGui::End();
			}

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			m_Window->OnUpdate();
		}
	}

	// The method that is called by the dispatcher when a event of the 
	// type WindowCloseEvent is triggered
	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		// Cleanup
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
		return true;
	}

}


int main(void)
{
	std::unique_ptr<GLCore::Application> app = std::make_unique<GLCore::Application>();
	app->Run();


	return 0;
}