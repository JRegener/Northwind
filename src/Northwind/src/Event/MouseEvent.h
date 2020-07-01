#pragma once

#include "Event/Event.h"

namespace Northwind {

	class MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent (float x, float y)
			: m_MouseX (x), m_MouseY (y) {}

		inline float getX () const { return m_MouseX; }
		inline float getY () const { return m_MouseY; }

		std::string toString () const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
			return ss.str ();
		}

		static EventType getStaticType () { return EventType::MouseMoved; }
		virtual EventType getEventType () const override { return getStaticType (); }
		virtual const char * getName () const override { return "MouseMoved"; }

		virtual int getCategoryFlags () const override { return EventCategoryMouse | EventCategoryInput; }
	private:
		float m_MouseX, m_MouseY;
	};

	class MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent (float xOffset, float yOffset)
			: m_XOffset (xOffset), m_YOffset (yOffset) {}

		inline float getXOffset () const { return m_XOffset; }
		inline float getYOffset () const { return m_YOffset; }

		std::string toString () const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << getXOffset () << ", " << getYOffset ();
			return ss.str ();
		}


		static EventType getStaticType () { return EventType::MouseScrolled; }
		virtual EventType getEventType () const override { return getStaticType (); }
		virtual const char * getName () const override { return "MouseScrolled"; }

		virtual int getCategoryFlags () const override { return EventCategoryMouse | EventCategoryInput; }

	private:
		float m_XOffset, m_YOffset;
	};

	class MouseButtonEvent : public Event
	{
	public:
		inline int getMouseButton () const { return m_Button; }

		virtual int getCategoryFlags () const override { return EventCategoryMouse | EventCategoryInput; }

	protected:
		MouseButtonEvent (int button)
			: m_Button (button) {}

		int m_Button;
	};

	class MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent (int button)
			: MouseButtonEvent (button) {}

		std::string toString () const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_Button;
			return ss.str ();
		}

		static EventType getStaticType () { return EventType::MouseButtonPressed; }
		virtual EventType getEventType () const override { return getStaticType (); }
		virtual const char * getName () const override { return "MouseButtonPressed"; }
	};

	class MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent (int button)
			: MouseButtonEvent (button) {}

		std::string toString () const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_Button;
			return ss.str ();
		}

		static EventType getStaticType () { return EventType::MouseButtonReleased; }
		virtual EventType getEventType () const override { return getStaticType (); }
		virtual const char * getName () const override { return "MouseButtonReleased"; }
	};

}