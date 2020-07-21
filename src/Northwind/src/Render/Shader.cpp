#include "Shader.h"

#include "Render/RendererAPI.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Northwind {



	Ref<Shader> Shader::Create(const std::string& sourceCode)
	{
		switch (RendererAPI::getAPI()) {
			case RendererAPI::API::None: NW_CORE_ASSERT(false, "Shader::None is not supported!"); return nullptr;
			case RendererAPI::API::Vulkan: NW_CORE_ASSERT(false, "Shader::Vulkan is not supported!"); return nullptr;
			case RendererAPI::API::OpenGL: return ;
		}

		//TODO:
		return nullptr;
	}

}