#pragma once

#include "Core/Core.h"
#include "Event/Event.h"


namespace Northwind {

	class Layer
	{
	public:

		explicit Layer (const std::string& name = "Layer");

		virtual ~Layer ();

		virtual void OnAttach () {}
		virtual void OnDetach () {}
		virtual void OnUpdate () {}
		virtual void OnEvent (Event & event) {}

		virtual void OnImGuiRender() {}

		inline std::string getName () const { return m_name; }
	private:
		std::string m_name;
	};

}

