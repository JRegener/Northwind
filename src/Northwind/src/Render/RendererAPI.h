#pragma once

#include "glm/glm.hpp"

namespace Northwind {

	class RendererAPI {

	public:
		enum class API {
			None = 0,
			OpenGL,
		};

	public:
		virtual void init() = 0;
		virtual void setViewPort(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
		virtual void setClearColor(const glm::vec3& color) = 0;
		virtual void clear() = 0;

		virtual ~RendererAPI() {}

		inline static API getAPI() { return s_API; }

		static Owned<RendererAPI> Create();
	private:
		static API s_API;
	};

}