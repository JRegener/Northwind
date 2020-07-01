#include "Northwind.h"
#include "Core/Core.h"
#include "Core/EntryPoint.h"
#include "Core/Layer.h"
#include "Event/Event.h"

#define NW_LOG
#define NW_CLIENT_LOG

class ExampleLayer : public Northwind::Layer {

public:
	ExampleLayer() : Layer ("ExampleLayer") {}

	virtual ~ExampleLayer () = default;

	virtual void OnAttach() override {}
	virtual void OnDetach() override {}

	virtual void OnUpdate() override {
		NW_CLIENT_TRACE ("{0}", m_name);
	}
	virtual void OnEvent (Northwind::Event & event) override  {
		NW_CLIENT_TRACE ("{0}", event);
	}
};

class SandBox : public Northwind::Application {
public:
	SandBox()
	{
		pushLayer (new ExampleLayer ());
	}

	~SandBox()
	{
	}
};

std::unique_ptr<Northwind::Application> Northwind::CreateApplication() {
	return std::make_unique<SandBox>();
}

