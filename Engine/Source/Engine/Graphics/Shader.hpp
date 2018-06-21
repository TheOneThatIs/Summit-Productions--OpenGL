#pragma once
#include<string>


namespace toti {


	class Shader {
		struct ShaderSource;
		unsigned int programID;

	public:
		Shader();

		ShaderSource parseShader(const std::string& filepath);
		unsigned int compileShader(unsigned int type, const std::string& source);
		unsigned int createProgram(const std::string& vertexShader, const std::string& fragmentShader);


		void deleteProgram();

		// Getters
		unsigned int getProgramID();
	};
}