#pragma once
#include<GL\glew.h>

namespace toti {
	class ArrayBuffer {
		unsigned int bufferID;
		unsigned int ibo; // Index Buffer Array

	public:
		ArrayBuffer();

		void fill(GLuint buffer, GLsizei size, void *data, GLenum usage);
	};
}