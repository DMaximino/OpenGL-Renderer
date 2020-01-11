#pragma once
#include "Test.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"
#include <memory>
#include <GLFW/glfw3.h>
#include "CameraController.h"


namespace test {

	class TestDrawCube : public Test
	{
	public:
		TestDrawCube(WindowProperties window);
		~TestDrawCube();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	private:
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<VertexBuffer> m_ColorVertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<Shader> m_Shader;

		bool m_EditMode;
		GLFWwindow* m_Window;
		CameraController m_CameraController;
	
	};
}