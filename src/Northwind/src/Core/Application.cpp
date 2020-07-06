#include "Application.h"

#include <GLFW/glfw3.h>
#include "Event/ApplicationEvent.h"

namespace Northwind {

	Application* Application::s_Instance = nullptr;

	Application::Application() : m_running(true)
	{
		NW_PROFILE_FUNC();

		NW_CORE_ASSERT(!s_Instance, "Application already exists!");

		s_Instance = this;
		m_window = Window::Create();
		m_window->setEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
		m_imGuiLayer = CreateOwned<ImGuiLayer>();

		//pushOverlay(m_imGuiLayer.get());
	}

	Application::~Application() {

	}

	void Application::Run() {
		NW_PROFILE_FUNC();

		while (m_running) {
			glClearColor(1, 0, 0, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			for (auto it : m_layerStack) {
				it->OnUpdate();
			}

			//m_imGuiLayer->Begin();
			//for (auto it : m_layerStack) {
			//	it->OnImGuiRender();
			//}
			//m_imGuiLayer->End();

			m_window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e)
	{
		NW_PROFILE_FUNC();

		NW_CORE_TRACE("{0}", e);

		EventDispatcher dispatcher(e);
		dispatcher.dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this));

		for (auto it = m_layerStack.rbegin(); it != m_layerStack.rend(); ++it) {
			(*it)->OnEvent(e);
			if (e.handled)
				break;
		}
	}

	void Application::pushLayer(const Ref<Layer>& layer)
	{
		NW_PROFILE_FUNC();

		m_layerStack.pushLayer(layer);
		layer->OnAttach();
	}

	void  Application::pushOverlay(const Ref<Layer>& overlay)
	{
		NW_PROFILE_FUNC();

		m_layerStack.pushOverlay(overlay);
		overlay->OnAttach();
	}

	bool Application::OnWindowClose()
	{
		NW_PROFILE_FUNC();

		m_running = false;
		return true;
	}
}
