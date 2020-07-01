#include "WindowsWindow.h"

#include "Event/ApplicationEvent.h"
#include "Event/KeyEvent.h"
#include "Event/MouseEvent.h"

namespace Northwind {

	std::unique_ptr<Window> Window::Create (const WindowProps & props) {
		return std::make_unique<WindowsWindow> (props);
	}

	WindowsWindow::WindowsWindow (const WindowProps & props) {
		init (props);
	}

	WindowsWindow::~WindowsWindow () {
		shutdown ();
	}

	void WindowsWindow::OnUpdate () {
		glfwPollEvents ();
		glfwSwapBuffers (m_window);
	}

	void WindowsWindow::setVSync (bool enabled) {
		if (enabled) {
			glfwSwapInterval (1);
		}
		else {
			glfwSwapInterval (0);
		}

		m_data.vSync = enabled;
	}

	bool WindowsWindow::isVSync () {
		return m_data.vSync;
	}

	void WindowsWindow::init (const WindowProps & props) {
		static bool GLFWInitialized = false;

		if (!GLFWInitialized) {
			int success = glfwInit ();
			NW_CORE_ASSERT (success, "Could not init GLFW");

			GLFWInitialized = false;
		}

		m_window = glfwCreateWindow ((int)props.width, (int)props.height, 
			props.title.c_str(), nullptr, nullptr);

		glfwMakeContextCurrent (m_window);
		glfwSetWindowUserPointer (m_window, &m_data);
		setVSync (true);

		// set GLFW callbacks

		glfwSetWindowSizeCallback (m_window, [](GLFWwindow * window, int width, int height) {
			WindowData & data = *(WindowData*)glfwGetWindowUserPointer (window);

			WindowResizeEvent event (width, height);
			data.eventCallback (event);
			data.width = width;
			data.height = height;
		});

		glfwSetWindowCloseCallback (m_window, [](GLFWwindow * window) {
			WindowData & data = *(WindowData*)glfwGetWindowUserPointer (window);
			WindowCloseEvent event;
			data.eventCallback (event);
		});

		glfwSetKeyCallback (m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			WindowData & data = *(WindowData*)glfwGetWindowUserPointer (window);

			switch (action) {
			case GLFW_PRESS:
			{
				KeyPressedEvent event(key, 0);
				data.eventCallback (event);
				break;
			}

			case GLFW_RELEASE:
			{
				KeyReleasedEvent event (key);
				data.eventCallback (event);
				break;
			}

			case GLFW_REPEAT:
			{
				KeyPressedEvent event (key, 1);
				data.eventCallback (event);
				break;
			}
			}
		});


		glfwSetCharCallback (m_window, [](GLFWwindow* window, unsigned int keycode)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer (window);

			KeyTypedEvent event (keycode);
			data.eventCallback (event);
		});

		glfwSetMouseButtonCallback (m_window, [](GLFWwindow* window, int button, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer (window);

			switch (action)
			{
			case GLFW_PRESS:
			{
				MouseButtonPressedEvent event (button);
				data.eventCallback (event);
				break;
			}
			case GLFW_RELEASE:
			{
				MouseButtonReleasedEvent event (button);
				data.eventCallback (event);
				break;
			}
			}
		});

		glfwSetScrollCallback (m_window, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer (window);

			MouseScrolledEvent event ((float)xOffset, (float)yOffset);
			data.eventCallback (event);
		});

		glfwSetCursorPosCallback (m_window, [](GLFWwindow* window, double xPos, double yPos)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer (window);

			MouseMovedEvent event ((float)xPos, (float)yPos);
			data.eventCallback (event);
		});
	}

	void WindowsWindow::shutdown () {
		glfwDestroyWindow (m_window);
	}
}
