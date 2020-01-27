#pragma once
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"
#include <memory>
#include "Cameras/CameraController.h"
#include "imgui/imgui.h"
#include "imgui/imfilebrowser.h"
#include "Application.h"

using namespace GLCore;

namespace ExperimentalApps {



	class DrawCubeLayer : public GLCore::Layer
	{
	public:
		DrawCubeLayer();
		~DrawCubeLayer();

		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate(float deltaTime) override;
		void OnRender();
		void OnImGuiRender() override;
		void OnEvent(GLCore::Event& e) override;
	private:
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<VertexBuffer> m_ColorVertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<Shader> m_TextureShader;
		std::unique_ptr<Shader> m_ColorShader;
		std::unique_ptr<Texture> m_Texture;
		std::unique_ptr<Texture> newTexture;

		bool m_EditMode;
		bool m_CtrlPressed;
		GLCore::CameraController m_CameraController;
		ImGui::FileBrowser m_FileDialog;
		std::string m_TexturePath;
		unsigned int m_TextureBuffer;
		int m_TextureWidth, m_TextureHeight;

	};

	class DrawCubeApp : public Application
	{
	public:
		DrawCubeApp()
			:Application("Draw cube") {
			PushLayer(new DrawCubeLayer());
		};
	};
}