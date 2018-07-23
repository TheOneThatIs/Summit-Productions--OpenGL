#pragma once
#include "ArrayBuffer.hpp"


namespace toti {
	ArrayBuffer::ArrayBuffer() {
		glGenBuffers(1, &ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	}

	void ArrayBuffer::fill(GLuint buffer, GLsizei size, void *data, GLenum usage) {
		glBufferData(buffer, size, data, usage);
	}
}