#pragma once

#include "nwpch.h"

#include "Core/Core.h"

namespace Northwind {
	
	enum class EventType {
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory {
		None = 0,
		EventCategoryApplication     = 1 << 0,
		EventCategoryInput           = 1 << 1,
		EventCategoryKeyboard        = 1 << 2,
		EventCategoryMouse           = 1 << 3,
		EventCategoryMouseButton     = 1 << 4,
	};

	class Event {
	public:
		bool handled = false;

		virtual EventType getEventType() const = 0;
		virtual int getCategoryFlags() const = 0;
		virtual const char* getName() const = 0;
		virtual std::string toString() const { return getName(); }

		inline bool isInCategory(EventCategory category) {
			return getCategoryFlags() & category;
		}

	};

	class EventDispatcher
	{
	public:
		EventDispatcher(Event& event)
			: m_event(event)
		{
		}

		// F will be deduced by the compiler
		template<typename T, typename F>
		bool dispatch(const F& func)
		{
			if (m_event.getEventType() == T::getStaticType())
			{
				m_event.handled = func(static_cast<T&>(m_event));
				return true;
			}
			return false;
		}
	private:
		Event& m_event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.toString();
	}
}