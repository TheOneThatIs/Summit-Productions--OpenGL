#include"IndexBuffer.hpp"

#include"Engine\Util\HelperFuntions.hpp"


namespace toti{

	IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int numIndicies) : numIndicies(numIndicies){
		callGL(glGenBuffers(1, &rendererID));
		callGL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID));
		callGL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndicies * sizeof(unsigned int), data, GL_STATIC_DRAW));
	}

	IndexBuffer::~IndexBuffer() {
		callGL(glDeleteBuffers(1, &rendererID));
	}

	void IndexBuffer::bind() const{
		callGL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID));
	}
	void IndexBuffer::unbind() const{
		callGL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	}
}