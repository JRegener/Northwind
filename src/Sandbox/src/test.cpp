#include "Northwind.h"
#include "Core/EntryPoint.h"

class SandBox : public Northwind::Application {
public:
	SandBox()
	{

	}

	~SandBox()
	{
	}
};

Northwind::Application * Northwind::CreateApplication() {
	return new SandBox();
}

