#include<GL\glew.h>
#include <GLFW\glfw3.h>
#include<iostream>
#include<string>

#include<Engine\Graphics\Shader.hpp>
#include<Engine\Util\ArrayBuffer.hpp>
#include<Engine\Util\HelperFuntions.hpp>
#include<Engine\Graphics\VertexBuffer.hpp>
#include<Engine\Graphics\IndexBuffer.hpp>
#include<Engine\Graphics\VertexArray.hpp>
#include<Engine\Graphics\Renderer.hpp>
#include<Engine\Graphics\Texture.hpp>

#include"Engine\Vendor\glm\glm.hpp"
#include"Engine\Vendor\glm\gtc\matrix_transform.hpp"
#include"Engine\Vendor\ImGUI\imgui.h"
#include"Engine\Vendor\ImGUI\imgui_impl_glfw_gl3.h"


int main(void) {
	GLFWwindow* window;

	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(960, 540, "Hello World", NULL, NULL);
	
	if (!window) {
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // VSync

	if (glewInit() != GLEW_OK)
		std::cout << "GLEW is not okay!" << std::endl;

	// Print the OpenGL Version
	std::cout << glGetString(GL_VERSION) << std::endl;

	float verticies[] = {
		50.0f,  50.0f,    1.0f,  1.0f,
		50.0f,  -50.0f,  1.0f,  0.0f,
		-50.0f,    -50.0f,  0.0f,  0.0f,
		-50.0f,    50.0f,    0.0f,  1.0f 
	};

	unsigned int indicies[] = {
		0, 1, 2,
		2, 3, 0
	};

	callGL(glEnable(GL_BLEND));
	callGL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)); // Set blend mode

	toti::VertexArray vertexArray;
	toti::VertexBuffer vertexBuffer(verticies, 4 * 4 * sizeof(float));

	toti::VertexBufferLayout layout;
	layout.push<float>(2);
	layout.push<float>(2);
	vertexArray.addBuffer(vertexBuffer, layout);

	toti::IndexBuffer indexBuffer(indicies, 6);
	
	glm::mat4 projection = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
	glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
	
	toti::Shader shader("Resources/Shaders/Basic.shader");
	shader.bind();

	toti::Texture texture("Resources/Textures/Test Image.png");
	texture.bind();
	shader.setUniform1i("uTexture", 0);

	//Unbind
	vertexArray.unbind();
	vertexBuffer.unbind();
	indexBuffer.unbind();
	shader.unbind();

	toti::Renderer renderer;

	// ImGUI
	ImGui::CreateContext();
	ImGui_ImplGlfwGL3_Init(window, true);
	ImGui::StyleColorsDark();
	


	float r = 0.0f;
	float increment = 0.005f;
	glm::vec3 translationA(0, 0, 0);
	glm::vec3 translationB(500, 200, 0);

	while (!glfwWindowShouldClose(window)){
		/* Render here */
		renderer.clear();

		ImGui_ImplGlfwGL3_NewFrame();

		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), translationA);
			glm::mat4 mvp = projection * view * model;
			shader.bind();
			shader.setUniformMat4f("uModelViewProj", mvp);

			renderer.draw(vertexArray, indexBuffer, shader);
		}

		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), translationB);
			glm::mat4 mvp = projection * view * model;
			shader.bind();
			shader.setUniformMat4f("uModelViewProj", mvp);

			renderer.draw(vertexArray, indexBuffer, shader);
		}


		if (r > 1.0f)
			increment = -0.005f;
		  else if(r < 0)increment = 0.005f;
		r += increment;


		{
			ImGui::SliderFloat3("Translation A", &translationA.x, 0.0f, 1280.0f);
			ImGui::SliderFloat3("Translation B", &translationB.x, 0.0f, 1280.0f);
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		}

		ImGui::Render();
		ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());


		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
	return 0;
}