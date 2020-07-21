#include "OpenGLShader.h"

#include <fstream>
#include "glad/glad.h"

namespace Northwind {

	Ref<OpenGLShader> OpenGLShader::Create(const std::string& vertexSource, const std::string & fragmentSource) {
		Ref<OpenGLShader> shader = nullptr;

		shader = CreateOwned<OpenGLShader>();
		shader->load(vertexSource, fragmentSource);

		return shader;
	}

	void OpenGLShader::load(const std::string& vertexSource, const std::string& fragmentSource) {


	}

	void OpenGLShader::compile(const std::unordered_map<GLuint, std::string>& source)
	{
		std::array<GLuint, 2> glShaders;
		size_t shaderIndex = 0;
		GLuint program = glCreateProgram();

		for (auto& s : source) {
			GLuint shader = glCreateShader(s.first);
			const GLchar *constSrc = (const GLchar*)s.second.c_str();
			glShaderSource(shader, 1, &constSrc, nullptr);
			glCompileShader(shader);

			GLint compileStatus;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus); 

			if (compileStatus == GL_FALSE) {
				GLint logLength;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);

				std::vector<GLchar> message;
				glGetShaderInfoLog(shader, logLength, &logLength, message.data());

				glDeleteShader(shader);

				NW_CORE_ERROR("{0}", message.data());
				NW_CORE_ASSERT(false, "Shader compilation failure!");
				break;
			}

			glAttachShader(program, shader);
			glShaders[shaderIndex++] = shader;
		}

		glLinkProgram(program);

		GLint linkStatus;
		glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
		if (linkStatus == GL_FALSE) {
			GLint logLength;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);

			std::vector<GLchar> message;
			glGetProgramInfoLog(program, logLength, &logLength, message.data());

			glDeleteProgram(program);

			for (auto shaderId : glShaders) {
				glDeleteShader(shaderId);
			}

			NW_CORE_ERROR("{0}", message.data());
			NW_CORE_ASSERT(false, "Program linking failure!");
			return;
		}

		for (auto shaderId : glShaders) {
			glDetachShader(program, shaderId);
			glDeleteShader(shaderId);
		}
	}

	void OpenGLShader::bind() {
		glUseProgram();
	}

	void OpenGLShader::unbind() {
		glUseProgram(0);
	}


}
