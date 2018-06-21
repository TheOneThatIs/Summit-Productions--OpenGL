#pragma once
#include<GL\glew.h>

namespace toti {
	class ArrayBuffer {
		unsigned int bufferID;

	public:
		ArrayBuffer();

		void fill(GLuint buffer, GLsizei size, void *data, GLenum usage);
	};
}