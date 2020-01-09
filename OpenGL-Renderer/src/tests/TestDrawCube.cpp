#include "TestDrawCube.h"
#include "Renderer.h"
#include "imgui/imgui.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

test::TestDrawCube::TestDrawCube()
	: m_Translation(1.0f, 1.0f, 1.0f), m_Rotation(1.0f, 1.0f, 1.0f), m_Angle(1.0f)
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

	unsigned int indexes[36];


	for (unsigned int i = 0; i < 36; i++)
		indexes[i] = i;

	float positionsAndColors[216];
	unsigned int j = 0;
	for (unsigned int i = 0; i < 216; i = i + 6)
	{
		positionsAndColors[i] = positions[j];
		positionsAndColors[i + 1] = positions[j + 1];
		positionsAndColors[i + 2] = positions[j + 2];
		positionsAndColors[i + 3] = colors[j];
		positionsAndColors[i + 4] = colors[j + 1];
		positionsAndColors[i + 5] = colors[j + 2];
		j += 3;
	}

	// Enable depth test
	GLCall(glEnable(GL_DEPTH_TEST));
	// Accept fragment if it closer to the camera than the former one
	GLCall(glDepthFunc(GL_LESS));


	m_VAO = std::make_unique<VertexArray>();
	// If vertex buffer were created in the constructor on the stack, once the program leaves the constructor 
	// the vertex buffer would be deleted and once this object is deleted from the CPU it is deleted from the GPU as well
	m_VertexBuffer = std::make_unique<VertexBuffer>(positionsAndColors, 12 * 3 * 6 * sizeof(float));

	VertexBufferLayout layout;
	layout.Push<float>(3); // cube coordinates
	layout.Push<float>(3); // cube vertice colors
	m_VAO->AddBuffer(*m_VertexBuffer, layout);


	m_IndexBuffer = std::make_unique<IndexBuffer>(indexes, 36);

	m_Shader = std::make_unique<Shader>("resources/shaders/DrawCube.shader");
	m_Shader->Bind();
	//m_Shader->SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);



}

test::TestDrawCube::~TestDrawCube()
{
	GLCall(glDisable(GL_DEPTH_TEST));
}

void test::TestDrawCube::OnUpdate(float deltaTime)
{
}

void test::TestDrawCube::OnRender()
{
	GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
	// Clear the screen
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

	Renderer renderer;

	glm::mat4 proj = glm::ortho(-4.0f, 4.0f, -4.0f, 4.0f, -5.0f, 5.0f);
	glm::mat4 view = glm::rotate(glm::mat4(1.0f), m_Angle, m_Rotation);
	glm::mat4 model = glm::translate(glm::mat4(1.0f), m_Translation);
	glm::mat4 mvp = proj * view * model;
	m_Shader->Bind();
	m_Shader->SetUniformMat4f("u_MVP", mvp);


	renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
	//glDrawArrays(GL_TRIANGLES, 0, 12 * 3);


}

void test::TestDrawCube::OnImGuiRender()
{
	ImGui::SliderFloat3("Translation", &m_Translation.x, -5.0f, 5.0f);
	ImGui::SliderFloat3("Rotation", &m_Rotation.x, -5.0f, 5.0f);
	ImGui::SliderFloat("Angle", &m_Angle, -5.0f, 5.0f);
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}
