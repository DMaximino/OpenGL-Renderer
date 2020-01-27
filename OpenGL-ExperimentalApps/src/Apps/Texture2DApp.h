#pragma once
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"
#include <memory>
#include "Application.h"

using namespace GLCore;

namespace ExperimentalApps {



	class Texture2DLayer : public GLCore::Layer
	{
	public:
		Texture2DLayer();
		~Texture2DLayer();
		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate(float deltaTime) override;
		void OnRender();
		void OnImGuiRender() override;
	private:
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<Texture> m_Texture;

		glm::mat4 m_Proj;
		glm::mat4 m_View;
		glm::vec3 m_TranslationA;
		glm::vec3 m_TranslationB;
	};

	class Texture2DApp : public Application
	{
	public:
		Texture2DApp()
			:Application("TestTexture2D") {
			PushLayer(new Texture2DLayer());
		};
	};

}