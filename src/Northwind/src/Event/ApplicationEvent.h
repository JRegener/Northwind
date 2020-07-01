#pragma once

#include "Event/Event.h"

namespace Northwind {

	class WindowCloseEvent : public Event {
	public:

		WindowCloseEvent () = default;

		static EventType getStaticType () { return EventType::WindowClose; }
		virtual EventType getEventType () const override { return getStaticType (); }
		virtual const char * getName () const override { return "WindowClose"; }

		virtual int getCategoryFlags () const override { return EventCategoryApplication; }
	};

	class WindowResizeEvent : public Event {
	public:

		WindowResizeEvent (uint32_t width, uint32_t height) :
			m_width (width), m_height (height) {};

		inline uint32_t getWidth () { return m_width; }
		inline uint32_t getHeight () { return m_height; }

		std::string toString () const override {
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_width << ", " << m_height;
			return ss.str ();
		}

		static EventType getStaticType () { return EventType::WindowResize; }
		virtual EventType getEventType () const override { return getStaticType (); }
		virtual const char * getName () const override { return "WindowResize"; }

		virtual int getCategoryFlags () const override { return EventCategoryApplication; }

	private:

		uint32_t m_width, m_height;
	};

	class AppTickEvent : public Event {
	public:

		AppTickEvent () = default;

		static EventType getStaticType () { return EventType::AppTick; }
		virtual EventType getEventType () const override { return getStaticType (); }
		virtual const char * getName () const override { return "AppTick"; }

		virtual int getCategoryFlags () const override { return EventCategoryApplication; }
	};

	class AppUpdateEvent : public Event {
	public:

		AppUpdateEvent () = default;

		static EventType getStaticType () { return EventType::AppUpdate; }
		virtual EventType getEventType () const override { return getStaticType (); }
		virtual const char * getName () const override { return "AppUpdate"; }

		virtual int getCategoryFlags () const override { return EventCategoryApplication; }
	};

	class AppRenderEvent : public Event {
	public:

		AppRenderEvent () = default;

		static EventType getStaticType () { return EventType::AppRender; }
		virtual EventType getEventType () const override { return getStaticType (); }
		virtual const char * getName () const override { return "AppRender"; }

		virtual int getCategoryFlags () const override { return EventCategoryApplication; }
	};
}