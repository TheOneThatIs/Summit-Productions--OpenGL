#include"Renderer.hpp"

namespace toti {
	Renderer::Renderer() {}
	Renderer::~Renderer(){}



	void Renderer::draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const {
		shader.bind();
		va.bind();
		ib.bind();
	
		callGL(glDrawElements(GL_TRIANGLES, ib.getNumIndicies(), GL_UNSIGNED_INT, nullptr));
	}

	void Renderer::clear() const{
		glClear(GL_COLOR_BUFFER_BIT);
	}
}