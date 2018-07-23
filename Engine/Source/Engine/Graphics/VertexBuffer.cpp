#include"VertexBuffer.hpp"

#include"Engine\Util\HelperFuntions.hpp"

namespace toti{

	VertexBuffer::VertexBuffer(const void* data, unsigned int size) {
		callGL(glGenBuffers(1, &rendererID));
		callGL(glBindBuffer(GL_ARRAY_BUFFER, rendererID));
		callGL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
	}

	VertexBuffer::~VertexBuffer() {
		callGL(glDeleteBuffers(1, &rendererID));
	}

	void VertexBuffer::bind() const {
		callGL(glBindBuffer(GL_ARRAY_BUFFER, rendererID));
	}
	void VertexBuffer::unbind() const {
		callGL(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}
}