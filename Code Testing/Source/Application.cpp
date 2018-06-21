#include<GL\glew.h>
#include <GLFW\glfw3.h>
#include<iostream>
#include<string>

#include<Engine\Graphics\Shader.hpp>
#include<Engine\Util\ArrayBuffer.hpp>


int main(void) {
	GLFWwindow* window;

	if (!glfwInit())
		return -1;

	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	
	
	if (!window) {
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
		std::cout << "GLEW is not okay!" << std::endl;

	// Print the OpenGL Version
	std::cout << glGetString(GL_VERSION) << std::endl;

	float verticies[6] = {
		-1.0f, -1.0f,
		1.0f, -1.0f,
		0.0f, 1.0f
	};

	
	toti::ArrayBuffer buffer;
	buffer.fill(GL_ARRAY_BUFFER, 6 * sizeof(float), verticies, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, false, sizeof(float) * 2, 0);
	glEnableVertexAttribArray(0);

	toti::Shader shader;
	glUseProgram(shader.getProgramID());

	while (!glfwWindowShouldClose(window)){
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, 3);


		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	shader.deleteProgram();

	glfwTerminate();
	return 0;
}