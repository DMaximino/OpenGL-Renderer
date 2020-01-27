#include "DrawMultipleObjectsApp.h"
#include "Renderer.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "stb_image/stb_image.h"
#include "Inputs/Input.h"
// TODO: Get rid of glfw include
#include "GLFW/glfw3.h"


ExperimentalApps::DrawMultipleObjectsLayer::DrawMultipleObjectsLayer()
	: m_CameraController(), m_EditMode(true), m_CtrlPressed(false), m_FileDialog()
{

}

ExperimentalApps::DrawMultipleObjectsLayer::~DrawMultipleObjectsLayer()
{

}

void ExperimentalApps::DrawMultipleObjectsLayer::OnAttach()
{
	// Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
	// A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
	const float positions[] = {
	-1.0f,-1.0f,-1.0f, // triangle 1 : begin
	-1.0f,-1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f, // triangle 1 : end
	1.0f, 1.0f,-1.0f, // triangle 2 : begin
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f,-1.0f, // triangle 2 : end
	1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f,-1.0f,
	1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f,-1.0f, 1.0f,
	1.0f,-1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f,-1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f,-1.0f,
	-1.0f, 1.0f,-1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f,-1.0f, 1.0f
	};

	const float pyramidPositions[] = {
		2.0f, 2.0f, 2.0f,
		2.0f, 2.0f, 3.0f,
		2.5f, 3.0f, 2.5f,

		2.0f, 2.0f, 3.0f,
		3.0f, 2.0f, 3.0f,
		2.5f, 3.0f, 2.5f,

		3.0f, 2.0f, 3.0f,
		3.0f, 2.0f, 2.0f,
		2.5f, 3.0f, 2.5f,

		3.0f, 2.0f, 2.0f,
		2.0f, 2.0f, 2.0f,
		2.5f, 3.0f, 2.5f,

		2.0f, 2.0f, 2.0f,
		2.0f, 2.0f, 3.0f,
		3.0f, 2.0f, 3.0f,

		3.0f, 2.0f, 3.0f,
		3.0f, 2.0f, 2.0f,
		2.0f, 2.0f, 2.0f

	};

	const float pyramidColors[] =
	{
		0.583f,  0.771f,  0.014f,
	0.609f,  0.115f,  0.436f,
	0.327f,  0.483f,  0.844f,
	0.822f,  0.569f,  0.201f,
	0.435f,  0.602f,  0.223f,
	0.310f,  0.747f,  0.185f,
	0.597f,  0.770f,  0.761f,
	0.559f,  0.436f,  0.730f,
	0.359f,  0.583f,  0.152f,
	0.483f,  0.596f,  0.789f,
	0.559f,  0.861f,  0.639f,
	0.195f,  0.548f,  0.859f,
	0.597f,  0.770f,  0.761f,
	0.559f,  0.436f,  0.730f,
	0.359f,  0.583f,  0.152f,
	0.483f,  0.596f,  0.789f,
	0.559f,  0.861f,  0.639f,
	0.195f,  0.548f,  0.859f
	};

	const float colors[] = {
	0.583f,  0.771f,  0.014f,
	0.609f,  0.115f,  0.436f,
	0.327f,  0.483f,  0.844f,
	0.822f,  0.569f,  0.201f,
	0.435f,  0.602f,  0.223f,
	0.310f,  0.747f,  0.185f,
	0.597f,  0.770f,  0.761f,
	0.559f,  0.436f,  0.730f,
	0.359f,  0.583f,  0.152f,
	0.483f,  0.596f,  0.789f,
	0.559f,  0.861f,  0.639f,
	0.195f,  0.548f,  0.859f,
	0.014f,  0.184f,  0.576f,
	0.771f,  0.328f,  0.970f,
	0.406f,  0.615f,  0.116f,
	0.676f,  0.977f,  0.133f,
	0.971f,  0.572f,  0.833f,
	0.140f,  0.616f,  0.489f,
	0.997f,  0.513f,  0.064f,
	0.945f,  0.719f,  0.592f,
	0.543f,  0.021f,  0.978f,
	0.279f,  0.317f,  0.505f,
	0.167f,  0.620f,  0.077f,
	0.347f,  0.857f,  0.137f,
	0.055f,  0.953f,  0.042f,
	0.714f,  0.505f,  0.345f,
	0.783f,  0.290f,  0.734f,
	0.722f,  0.645f,  0.174f,
	0.302f,  0.455f,  0.848f,
	0.225f,  0.587f,  0.040f,
	0.517f,  0.713f,  0.338f,
	0.053f,  0.959f,  0.120f,
	0.393f,  0.621f,  0.362f,
	0.673f,  0.211f,  0.457f,
	0.820f,  0.883f,  0.371f,
	0.982f,  0.099f,  0.879f
	};

	const float uvData[] = {
	0.000059f, 1.0f - 0.000004f,
	0.000103f, 1.0f - 0.336048f,
	0.335973f, 1.0f - 0.335903f,
	1.000023f, 1.0f - 0.000013f,
	0.667979f, 1.0f - 0.335851f,
	0.999958f, 1.0f - 0.336064f,
	0.667979f, 1.0f - 0.335851f,
	0.336024f, 1.0f - 0.671877f,
	0.667969f, 1.0f - 0.671889f,
	1.000023f, 1.0f - 0.000013f,
	0.668104f, 1.0f - 0.000013f,
	0.667979f, 1.0f - 0.335851f,
	0.000059f, 1.0f - 0.000004f,
	0.335973f, 1.0f - 0.335903f,
	0.336098f, 1.0f - 0.000071f,
	0.667979f, 1.0f - 0.335851f,
	0.335973f, 1.0f - 0.335903f,
	0.336024f, 1.0f - 0.671877f,
	1.000004f, 1.0f - 0.671847f,
	0.999958f, 1.0f - 0.336064f,
	0.667979f, 1.0f - 0.335851f,
	0.668104f, 1.0f - 0.000013f,
	0.335973f, 1.0f - 0.335903f,
	0.667979f, 1.0f - 0.335851f,
	0.335973f, 1.0f - 0.335903f,
	0.668104f, 1.0f - 0.000013f,
	0.336098f, 1.0f - 0.000071f,
	0.000103f, 1.0f - 0.336048f,
	0.000004f, 1.0f - 0.671870f,
	0.336024f, 1.0f - 0.671877f,
	0.000103f, 1.0f - 0.336048f,
	0.336024f, 1.0f - 0.671877f,
	0.335973f, 1.0f - 0.335903f,
	0.667969f, 1.0f - 0.671889f,
	1.000004f, 1.0f - 0.671847f,
	0.667979f, 1.0f - 0.335851f
	};

	unsigned int pyramidIndexes[18];

	for (unsigned int i = 0; i < 18; i++)
		pyramidIndexes[i] = i;

	float pyramidPositionColor[108];
	unsigned int j = 0;
	for (unsigned int i = 0; i < 108; i = i + 6)
	{
		pyramidPositionColor[i] = pyramidPositions[j];
		pyramidPositionColor[i + 1] = pyramidPositions[j + 1];
		pyramidPositionColor[i + 2] = pyramidPositions[j + 2];
		pyramidPositionColor[i + 3] = pyramidColors[j];
		pyramidPositionColor[i + 4] = pyramidColors[j + 1];
		pyramidPositionColor[i + 5] = pyramidColors[j + 2];
		j += 3;
	}

	unsigned int indexes[36];
	for (unsigned int i = 0; i < 36; i++)
		indexes[i] = i;

	float positionColorUV[288];
	j = 0;
	unsigned int k = 0;
	for (unsigned int i = 0; i < 288; i = i + 8)
	{
		positionColorUV[i] = positions[j];
		positionColorUV[i + 1] = positions[j + 1];
		positionColorUV[i + 2] = positions[j + 2];
		positionColorUV[i + 3] = colors[j];
		positionColorUV[i + 4] = colors[j + 1];
		positionColorUV[i + 5] = colors[j + 2];
		positionColorUV[i + 6] = uvData[k];
		positionColorUV[i + 7] = uvData[k + 1];
		j += 3;
		k += 2;
	}

	// Enable depth test
	GLCall(glEnable(GL_DEPTH_TEST));
	// Accept fragment if it closer to the camera than the former one
	GLCall(glDepthFunc(GL_LESS));
	// Cull triangles which normal is not towards the camera
	GLCall(glEnable(GL_CULL_FACE));


	m_VAO = std::make_unique<VertexArray>();
	// If vertex buffer were created in the constructor on the stack, once the program leaves the constructor 
	// the vertex buffer would be deleted and once this object is deleted from the CPU it is deleted from the GPU as well
	m_VertexBuffer = std::make_unique<VertexBuffer>(positionColorUV, 12 * 3 * 8 * sizeof(float));
	m_PyramidVertexBuffer = std::make_unique<VertexBuffer>(pyramidPositionColor, 108 * sizeof(float));


	m_IndexBuffer = std::make_unique<IndexBuffer>(indexes, 36);
	m_PyramidIndexBuffer = std::make_unique<IndexBuffer>(indexes, 18);

	//m_TextureShader = std::make_unique<Shader>("resources/shaders/Texture.shader");
	m_ColorShader = std::make_unique<Shader>("resources/shaders/Color.shader");
	//m_TextureShader->Bind();
	m_ColorShader->Bind();
	//m_Shader->SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);

	//m_Texture = std::make_unique<Texture>("resources/textures/el-capitan.png");
	//m_Shader->SetUniform1i("u_Texture", 0);
}

void ExperimentalApps::DrawMultipleObjectsLayer::OnDetach()
{
	GLCall(glDisable(GL_DEPTH_TEST));
}

void ExperimentalApps::DrawMultipleObjectsLayer::OnUpdate(float deltaTime)
{
	if (GLCore::Input::IsKeyPressed(GLFW_KEY_LEFT_SHIFT))
		m_CtrlPressed = true;

	if (m_CtrlPressed)
	{
		if (GLCore::Input::IsKeyPressed(GLFW_KEY_ESCAPE))
		{
			m_EditMode = !m_EditMode;
			m_CtrlPressed = false;
		}
	}

	if (m_EditMode == false)
	{

		//glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		m_CameraController.OnUpdate(deltaTime);
	}

	OnRender();
}

void ExperimentalApps::DrawMultipleObjectsLayer::OnRender()
{
	GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
	// Clear the screen
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

	Renderer renderer;

	{
		VertexBufferLayout layout;
		layout.Push<float>(3); // cube coordinates
		layout.Push<float>(3); // cube vertice colors
		layout.Push<float>(2); // cube vertice colors
		m_VAO->AddBuffer(*m_VertexBuffer, layout);

		glm::mat4 m_ProjectionMatrix = m_CameraController.GetProjectionMatrix();
		glm::mat4 m_ViewMatrix = m_CameraController.GetViewMatrix();
		glm::mat4 model1 = glm::mat4(1.0f);

		glm::mat4 mvp = m_ProjectionMatrix * m_ViewMatrix * model1;

		m_ColorShader->Bind();
		m_ColorShader->SetUniformMat4f("u_MVP", mvp);
		renderer.Draw(*m_VAO, *m_IndexBuffer, *m_ColorShader);
	}

	{
		VertexBufferLayout layout;
		layout.Push<float>(3); // cube coordinates
		layout.Push<float>(3); // cube vertice colors
		m_VAO->AddBuffer(*m_PyramidVertexBuffer, layout);
		
		glm::mat4 m_ProjectionMatrix = m_CameraController.GetProjectionMatrix();
		glm::mat4 m_ViewMatrix = m_CameraController.GetViewMatrix();
		glm::mat4 model1 = glm::mat4(1.0f);

		glm::mat4 mvp = m_ProjectionMatrix * m_ViewMatrix * model1;

		m_ColorShader->Bind();
		m_ColorShader->SetUniformMat4f("u_MVP", mvp);
		renderer.Draw(*m_VAO, *m_PyramidIndexBuffer, *m_ColorShader);
	}

}

//TODO: Move to a string utilities class
//std::string GetFileName(const std::string& s) {
//
//	char sep = '/';
//
//#ifdef _WIN32
//	sep = '\\';
//#endif
//
//	size_t i = s.rfind(sep, s.length());
//	if (i != std::string::npos) {
//		return(s.substr(i + 1, s.length() - i));
//	}
//
//	return("");
//}

//TODO: Understand why the texture is shown upside down
void ExperimentalApps::DrawMultipleObjectsLayer::OnImGuiRender()
{
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::Spacing();
	if (ImGui::Button("Add Texture"))
		m_FileDialog.Open();
	m_FileDialog.Display();

	if (m_FileDialog.HasSelected())
	{
		std::cout << "Selected filename: " << m_FileDialog.GetSelected().string() << std::endl;
		m_TexturePath = m_FileDialog.GetSelected().string();
		if (m_TexturePath.empty() == false)
		{
			m_Texture = std::make_unique<Texture>(m_TexturePath.c_str());
			m_TextureBuffer = m_Texture->GetRenderID();
			m_TextureShader->Bind();
			m_TextureShader->SetUniform1i("u_Texture", 0);
		}
		m_FileDialog.ClearSelected();
	}

	if (m_TexturePath.empty() == false)
	{
		//ImGui::Text("Texture name: %s", GetFileName(m_TexturePath).c_str());
		ImGui::Text("size = %d x %d", m_Texture->GetWidth(), m_Texture->GetHeight());
		ImGui::Image((void*)(intptr_t)m_TextureBuffer, ImVec2(300.0f, 200.0f));
	}
}
