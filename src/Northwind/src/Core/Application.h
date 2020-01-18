#pragma once

#include "Core.h"

namespace Northwind {
	class Application {
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	//to be defined in CLIENT
	Application * CreateApplication();
}