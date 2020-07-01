#pragma once

#include "nwpch.h"
#include "Core/Core.h"
#include "Event/Event.h"

namespace Northwind {

	struct WindowProps {
		std::string title;
		uint32_t width;
		uint32_t height;


		WindowProps (const std::string& title = "Northwind Engine",
			uint32_t width = 1280, uint32_t height = 720) :
			title (title), width (width), height (height)
		{}
	};

	class Window {
	public:
		using EventCallbackFn = std::function<void (Event&)>;

		virtual ~Window () {}

		virtual void OnUpdate () = 0;

		virtual uint32_t getWidth () const = 0;
		virtual uint32_t getHeight () const = 0;

		virtual void setEventCallback (const EventCallbackFn& callback) = 0;
		virtual void setVSync (bool enabled) = 0;
		virtual bool isVSync () = 0;

		static std::unique_ptr<Window> Create (const WindowProps & props = WindowProps ());
	};
}