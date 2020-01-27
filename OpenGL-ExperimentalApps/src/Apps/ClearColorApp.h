#pragma once
#include "Application.h"

using namespace GLCore;
namespace ExperimentalApps {


	class ClearColorLayer : public GLCore::Layer
	{
	public:
		ClearColorLayer();
		~ClearColorLayer();

		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate(float deltaTime) override;
		void OnRender();
		void OnImGuiRender() override;
	private:
		float m_ClearColor[4];
	};

	class ClearColorApp : public Application
	{
	public:
		ClearColorApp()
			:Application("TestClearColor") {
			PushLayer(new ClearColorLayer());
		};
	};

}