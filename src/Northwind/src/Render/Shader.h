#pragma once

#include "Northwind.h"

namespace Northwind {

	class Shader {

	public:
		virtual ~Shader() = 0;

		virtual void bind() = 0;
		virtual void unbind() = 0;

		static Ref<Shader> Create(const std::string & sourceCode);

	};

}