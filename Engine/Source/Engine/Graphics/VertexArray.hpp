#pragma once

#include"VertexBuffer.hpp"
#include"VertexBufferLayout.hpp"

namespace toti {
	class VertexArray {
	private:
		unsigned int rendererID;

	public:
		VertexArray();
		~VertexArray();

		void addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
		
		void bind() const;
		void unbind() const;
	};
}