#pragma once

#include "Northwind.h"
#include "Render/Shader.h"

namespace Northwind {

	class OpenGLShader : public Shader {

		virtual ~OpenGLShader() = default;

		void load(const std::string& vertexSource, const std::string& fragmentSource);
		void compile(const std::unordered_map<GLuint, std::string>& source);


		virtual void bind() override;
		virtual void unbind() override;

		static Ref<OpenGLShader> Create(const std::string& vertexSource, const std::string& fragmentSource);
	};

}