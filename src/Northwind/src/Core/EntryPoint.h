#pragma once 

#include "Northwind.h"

extern Northwind::Application * Northwind::CreateApplication();

int main(int argc, char ** argv) {
	Northwind::Log::Init();

	NW_CORE_INFO("inside core");
	NW_CLIENT_WARN("inside client");

	auto app = Northwind::CreateApplication();

	app->Run();

	delete app;
}