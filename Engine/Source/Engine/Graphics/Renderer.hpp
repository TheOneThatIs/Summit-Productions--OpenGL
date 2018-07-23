#pragma once

#include"VertexArray.hpp"
#include"IndexBuffer.hpp"
#include"Shader.hpp"

namespace toti {
	class Renderer {
	public:
		Renderer();
		~Renderer();

		void draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
		void clear() const;
	};
}