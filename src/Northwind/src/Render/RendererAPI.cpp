#include "Render/RendererAPI.h"

#include "Northwind.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Northwind {

	RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;

	Owned<RendererAPI> RendererAPI::Create() {

		switch (s_API) {

			case RendererAPI::API::None:	NW_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::Vulkan:	NW_CORE_ASSERT(false, "RendererAPI::Vulkan is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return CreateOwned<OpenGLRendererAPI>();

		}

		NW_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

}