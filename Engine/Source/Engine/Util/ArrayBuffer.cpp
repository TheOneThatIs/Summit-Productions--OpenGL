#pragma once
#include "ArrayBuffer.hpp"


namespace toti {
	ArrayBuffer::ArrayBuffer() {
		glGenBuffers(1, &bufferID);
		glBindBuffer(GL_ARRAY_BUFFER, bufferID);
	}

	void ArrayBuffer::fill(GLuint buffer, GLsizei size, void *data, GLenum usage) {
		glBufferData(buffer, size, data, usage);
	}
}