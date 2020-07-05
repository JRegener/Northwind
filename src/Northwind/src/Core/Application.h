#pragma once

#include "Core.h"
#include "Window.h"
#include "LayerStack.h"
#include "ImGui/ImGuiLayer.h"


namespace Northwind {
	class Application {
	public:
		explicit Application();
		virtual ~Application();

		void Run();

		void OnEvent (Event & e);
	
		void pushLayer (Layer * layer);
		void pushOverlay (Layer * overlay);

		Window& getWindow() { return *m_window.get(); }

		static Application& getInstance() { return *s_Instance; }

	private:
		bool OnWindowClose ();
	
	private:
		Owned<ImGuiLayer> m_imGuiLayer;
		Owned<Window> m_window;
		bool m_running;

		LayerStack m_layerStack;
		
		static Application * s_Instance;
	};

	//to be defined in CLIENT
	Owned<Application> CreateApplication();
}