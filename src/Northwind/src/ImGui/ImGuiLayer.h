#pragma once

#include "nwpch.h"
#include "Northwind.h"
#include "Core/Layer.h"

namespace Northwind {
	class ImGuiLayer : public Northwind::Layer {

	public:
		explicit ImGuiLayer();

		virtual void OnAttach();
		virtual void OnDetach();
		virtual void OnUpdate();
		virtual void OnEvent();


	};

}