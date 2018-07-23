#pragma once
#include"Engine\Util\HelperFuntions.hpp"
#include<GL\glew.h>
#include"Engine\Vendor\ImGUI\imgui.h"


namespace test {
	class Test {
	public:
		Test() {}
		virtual ~Test() {}

		virtual void update(float deltaTime){}
		virtual void render(){}
		virtual void imGuiRender(){}
	};
}