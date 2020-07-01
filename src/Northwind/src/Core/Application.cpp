#include "Application.h"

#include <GLFW/glfw3.h>
#include "Event/ApplicationEvent.h"

namespace Northwind {

	Application::Application () : 
		m_window(Window::Create ()), m_running(true)
	{
		m_window->setEventCallback (std::bind (&Application::OnEvent, this, std::placeholders::_1));
	}

	Application::~Application () {

	}

	void Application::Run () {
		while (m_running) {
			glClearColor (1, 0, 0, 1);
			glClear (GL_COLOR_BUFFER_BIT);

			for (auto it : m_layerStack) {
				it->OnUpdate ();
			}

			m_window->OnUpdate ();
		}
	}

	void Application::OnEvent (Event & e)
	{
		NW_CORE_TRACE ("{0}", e);

		EventDispatcher dispatcher (e);
		dispatcher.dispatch<WindowCloseEvent> (std::bind (&Application::OnWindowClose, this));

		for (auto it = m_layerStack.rbegin (); it != m_layerStack.rend (); ++it) {
			(*it)->OnEvent (e);
			if (e.handled)
				break;
		}
	}

	void Application::pushLayer (Layer * layer)
	{
		m_layerStack.pushLayer (layer);
		layer->OnAttach();
	}

	void Application::pushOverlay (Layer * overlay)
	{
		m_layerStack.pushOverlay (overlay);
		overlay->OnAttach();
	}

	bool Application::OnWindowClose ()
	{
		m_running = false;
		return true;
	}
}
