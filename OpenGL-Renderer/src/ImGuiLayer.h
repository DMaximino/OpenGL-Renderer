#pragma once

#include "Layer.h"
#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"

namespace GLCore {

	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void Begin();
		void End();

		virtual void OnEvent(Event& event);
		bool OnMouseButtonPressed(MouseButtonPressedEvent& e);
	private:
		float m_Time = 0.0f;
	};

}