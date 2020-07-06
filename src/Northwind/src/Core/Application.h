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
	
		void pushLayer(const Ref<Layer>& layer);
		void pushOverlay(const Ref<Layer>& overlay);

		Window& getWindow() { return *m_window.get(); }

		static Application& getInstance() { return *s_Instance; }

	private:
		bool OnWindowClose ();
	
	private:
		Owned<Window> m_window;
		bool m_running;

		LayerStack m_layerStack;
		
		Ref<ImGuiLayer> m_imGuiLayer;
		static Application * s_Instance;
	};

	//to be defined in CLIENT
	Owned<Application> CreateApplication();
}