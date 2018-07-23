#include"VertexArray.hpp"
#include"Engine\Util\HelperFuntions.hpp"

namespace toti {
	VertexArray::VertexArray(){
		callGL(glGenVertexArrays(1, &rendererID));
	}
	VertexArray::~VertexArray() {
		callGL(glDeleteVertexArrays(1, &rendererID));
	}


	void VertexArray::addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout) {
		bind();
		vb.bind();
		const auto& elements = layout.getElements();
		unsigned int offset = 0;
		for (unsigned int i = 0; i < elements.size(); i++) {
			const auto& element = elements[i];
			callGL(glEnableVertexAttribArray(i));
			callGL(glVertexAttribPointer(i, element.count, element.type, element.isNormalized, layout.getStride(), (const void*)offset));
			offset += element.count * VertexBufferElement::getSizeOfType(element.type);
		}
	}

	void VertexArray::bind() const {
		callGL(glBindVertexArray(rendererID));
	}

	void VertexArray::unbind() const {
		callGL(glBindVertexArray(0));
	}
}