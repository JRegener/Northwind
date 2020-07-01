#pragma once

#include "Core.h"
#include "Window.h"
#include "LayerStack.h"

namespace Northwind {
	class Application {
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent (Event & e);
	
		void pushLayer (Layer * layer);
		void pushOverlay (Layer * overlay);

	private:
		bool OnWindowClose ();
	
	private:
		std::unique_ptr<Window> m_window;
		bool m_running;

		LayerStack m_layerStack;
	};

	//to be defined in CLIENT
	std::unique_ptr<Application> CreateApplication();
}