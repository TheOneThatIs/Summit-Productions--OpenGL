#pragma once

#include<GL\glew.h>
#include<iostream>

#define ASSERT(x) if (!(x)) __debugbreak();
#define callGL(x) { clearGLErrors();\
	x;\
	ASSERT(logGLCall(#x, __FILE__, __LINE__)) }



static void clearGLErrors() {
	while (glGetError() != GL_NO_ERROR);
}

static bool logGLCall(const char* function, const char* file, int line) {
	while (GLenum error = glGetError()) {
		std::cout << "[OpenGL Error]" << function << std::endl;
		std::cout << error << std::endl;
		return false;
	}
	return true;
}

namespace toti {
	
}