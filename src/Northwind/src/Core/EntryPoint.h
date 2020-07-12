#pragma once 

#include "Northwind.h"

extern std::unique_ptr<Northwind::Application> Northwind::CreateApplication();

int main(int argc, char ** argv) {
	Northwind::Log::Init();

	NW_CORE_INFO("inside core");
	NW_CLIENT_WARN("inside client");

	auto app = Northwind::CreateApplication();

	NW_PROFILE_BEGIN("profile.json");

	app->Run();
	NW_PROFILE_END();
}