#pragma once

#include "Event/Event.h"

namespace Northwind {

	class KeyEvent : public Event {
	public:

		inline int getKeyCode() { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

	protected:

		KeyEvent(int keycode) :
			m_KeyCode(keycode) {}

		int m_KeyCode;
	};

	class KeyPressedEvent : public KeyEvent {
	public:

		KeyPressedEvent(int keyCode, int repeatCount) :
			KeyEvent(keyCode), m_RepeatCount(repeatCount) {}

		inline int getRepeatCount() { return m_RepeatCount; }

		std::string toString() const override {
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << ")";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)

	private:

		int m_RepeatCount;
	};

	class KeyReleasedEvent : public KeyEvent {
	public:

		KeyReleasedEvent(int keyCode) :
			KeyEvent(keyCode) {}

		std::string toString() const override {
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};

	class KeyTypedEvent : public KeyEvent {
	public:

		KeyTypedEvent(int keyCode) :
			KeyEvent(keyCode) {}

		std::string toString() const override {
			std::stringstream ss;
			ss << "KeyTypedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyTyped)
	};

}