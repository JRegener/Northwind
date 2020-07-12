#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Core/Window.h"

namespace Northwind {

	class WindowsWindow : public Window {
	public:

		WindowsWindow (const WindowProps& props);

		virtual ~WindowsWindow ();


		void OnUpdate () override;

		inline uint32_t getWidth () const override { return m_data.width; };
		inline uint32_t getHeight () const override { return m_data.height; };

		inline void setEventCallback (const EventCallbackFn & callback) override {
			m_data.eventCallback = callback;
		}
		void setVSync (bool enabled) override;
		bool isVSync () override;

		void* getNativeWindow() { return m_window; }

	private:
		virtual void init (const WindowProps & props);
		virtual void shutdown ();

	private:
		GLFWwindow * m_window;

		struct WindowData {
			std::string title;
			uint32_t width, height;
			bool vSync;

			EventCallbackFn eventCallback;
		};

		WindowData m_data;
	};

}