#include"Engine\Tests\TestClearColor.hpp"


namespace test {
	TestClearColor::TestClearColor() : clearColor{0.3f, 0.5f, 0.8f, 1.0f} {

	}
	TestClearColor::~TestClearColor() {

	}



	void TestClearColor::update(float deltaTime) {

	}
	void TestClearColor::render() {
		callGL(glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]));
		callGL(glClear(GL_COLOR_BUFFER_BIT));
	}
	void TestClearColor::imGuiRender() {
		ImGui::ColorEdit4("Clear Color", clearColor);
	}
}