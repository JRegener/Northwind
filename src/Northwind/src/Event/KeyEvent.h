#pragma once

#include "Event/Event.h"

namespace Northwind {

	class KeyEvent : public Event {
	public:

		inline int getKeyCode () { return m_KeyCode; }

		virtual int getCategoryFlags () const override {
			return EventCategoryKeyboard | EventCategoryInput;
		}

	protected:

		KeyEvent (int keycode) :
			m_KeyCode (keycode) {}

		int m_KeyCode;
	};

	class KeyPressedEvent : public KeyEvent {
	public:

		KeyPressedEvent (int keyCode, int repeatCount) :
			KeyEvent (keyCode), m_RepeatCount (repeatCount) {}

		inline int getRepeatCount () { return m_RepeatCount; }

		std::string toString () const override {
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << ")";
			return ss.str ();
		}

		static EventType getStaticType () { return EventType::KeyPressed; }
		virtual EventType getEventType () const override { return getStaticType (); }
		virtual const char * getName () const override { return "KeyPressed"; }

	private:

		int m_RepeatCount;
	};

	class KeyReleasedEvent : public KeyEvent {
	public:

		KeyReleasedEvent (int keyCode) :
			KeyEvent (keyCode) {}

		std::string toString () const override {
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str ();
		}

		static EventType getStaticType () { return EventType::KeyReleased; }
		virtual EventType getEventType () const override { return getStaticType (); }
		virtual const char * getName () const override { return "KeyReleased"; }
	};

	class KeyTypedEvent : public KeyEvent {
	public:

		KeyTypedEvent (int keyCode) :
			KeyEvent (keyCode) {}

		std::string toString () const override {
			std::stringstream ss;
			ss << "KeyTypedEvent: " << m_KeyCode;
			return ss.str ();
		}

		static EventType getStaticType () { return EventType::KeyTyped; }
		virtual EventType getEventType () const override { return getStaticType (); }
		virtual const char * getName () const override { return "KeyTyped"; }
	};

}