#include "Texture2DApp.h"
#include "Renderer.h"
#include "imgui/imgui.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

ExperimentalApps::Texture2DLayer::Texture2DLayer()
	: m_TranslationA(200,200,0), m_TranslationB(400,200,0),
	m_Proj(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f)),
	m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)))
{


}

ExperimentalApps::Texture2DLayer::~Texture2DLayer()
{
}

void ExperimentalApps::Texture2DLayer::OnAttach()
{
	float positions[] = {
			-50.0f, -50.0f, 0.0f, 0.0f, //0
			 50.0f, -50.0f, 1.0f, 0.0f, //1
			 50.0f,  50.0f, 1.0f, 1.0f, //2
			-50.0f,  50.0f, 0.0f, 1.0f  //3
	};

	unsigned int indexes[] = {
		0,1,2,
		2,3,0
	};

	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));


	m_VAO = std::make_unique<VertexArray>();
	// If vertex buffer were created in the constructor on the stack, once the program leaves the constructor 
	// the vertex buffer would be deleted and once this object is deleted from the CPU it is deleted from the GPU as well
	m_VertexBuffer = std::make_unique<VertexBuffer>(positions, 4 * 4 * sizeof(float));

	VertexBufferLayout layout;
	layout.Push<float>(2); // square coordinates
	layout.Push<float>(2); // texture coordinates
	m_VAO->AddBuffer(*m_VertexBuffer, layout);


	m_IndexBuffer = std::make_unique<IndexBuffer>(indexes, 6);

	m_Shader = std::make_unique<Shader>("resources/shaders/Basic.shader");
	m_Shader->Bind();
	m_Shader->SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);


	m_Texture = std::make_unique<Texture>("resources/textures/el-capitan.png");
	m_Shader->SetUniform1i("u_Texture", 0);
}

void ExperimentalApps::Texture2DLayer::OnDetach()
{
}

void ExperimentalApps::Texture2DLayer::OnUpdate(float deltaTime)
{
	OnRender();
}

void ExperimentalApps::Texture2DLayer::OnRender()
{
	GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
	GLCall(glClear(GL_COLOR_BUFFER_BIT));

	Renderer renderer;
	m_Texture->Bind();

	{
		glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationA);
		glm::mat4 mvp = m_Proj * m_View * model;
		m_Shader->Bind();
		m_Shader->SetUniformMat4f("u_MVP", mvp);

		renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
	}

	{
		glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationB);
		glm::mat4 mvp = m_Proj * m_View * model;
		m_Shader->Bind();
		m_Shader->SetUniformMat4f("u_MVP", mvp);

		renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
	}
}

void ExperimentalApps::Texture2DLayer::OnImGuiRender()
{
	ImGui::SliderFloat3("Translation A", &m_TranslationA.x, 0.0f, 960.0f);
	ImGui::SliderFloat3("Translation B", &m_TranslationB.x, 0.0f, 960.0f);
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}
