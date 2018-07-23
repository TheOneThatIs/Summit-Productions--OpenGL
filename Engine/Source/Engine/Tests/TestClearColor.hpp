#pragma once


#include"Engine\Tests\Test.hpp"


namespace test {
	class TestClearColor : public Test {
		float clearColor[4];
	public:
		TestClearColor();
		~TestClearColor();

		void update(float deltaTime) override;
		void render() override;
		void imGuiRender() override;
	};
}