#include "Northwind.h"
#include "Core/Core.h"
#include "Core/EntryPoint.h"
#include "Core/Layer.h"
#include "Event/Event.h"

#include "imgui.h"
#include "examples/imgui_impl_glfw.h"
#include "examples/imgui_impl_opengl3.h"


#include "GLFW/glfw3.h"

#define NW_LOG
#define NW_CLIENT_LOG

class ExampleLayer : public Northwind::Layer {

public:
	ExampleLayer() : Layer ("ExampleLayer") {}

	virtual ~ExampleLayer () = default;

	virtual void OnAttach() override {
		// TODO: framebuffer
	}

	virtual void OnDetach() override {}

	virtual void OnUpdate() override {
		NW_CLIENT_TRACE ("{0}", m_name);
	}

	virtual void OnEvent (Northwind::Event & event) override  {
		NW_CLIENT_TRACE ("{0}", event);
	}

	virtual void OnImGuiRender() override {
		// Create a window called "My First Tool", with a menu bar.
		bool my_tool_active = false;
		ImGui::Begin("My First Tool", &my_tool_active, ImGuiWindowFlags_MenuBar);
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Open..", "Ctrl+O")) { /* Do stuff */ }
				if (ImGui::MenuItem("Save", "Ctrl+S")) { /* Do stuff */ }
				if (ImGui::MenuItem("Close", "Ctrl+W")) { my_tool_active = false; }
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}

		// Plot some values
		const float my_values[] = { 0.2f, 0.1f, 1.0f, 0.5f, 0.9f, 2.2f };
		ImGui::PlotLines("Frame Times", my_values, IM_ARRAYSIZE(my_values));

		// Display contents in a scrolling region
		ImGui::TextColored(ImVec4(1, 1, 0, 1), "Important Stuff");
		ImGui::BeginChild("Scrolling");
		for (int n = 0; n < 50; n++)
			ImGui::Text("%04d: Some text", n);
		ImGui::EndChild();
		ImGui::End();
	}
};


class SandBox : public Northwind::Application {
public:
	SandBox() : m_exampleLayer(Northwind::CreateOwned<ExampleLayer>())
	{
		pushLayer (m_exampleLayer.get());
	}

	~SandBox()
	{
	}

private:
	Northwind::Owned<ExampleLayer> m_exampleLayer;
};

Northwind::Owned<Northwind::Application> Northwind::CreateApplication() {
	return Northwind::CreateOwned<SandBox>();
}

