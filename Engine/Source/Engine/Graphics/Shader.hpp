#pragma once
#include<string>
#include<unordered_map>
#include"Engine\Vendor\glm\glm.hpp"

namespace toti {
	struct ShaderSource {
		std::string vertexSource;
		std::string fragmentSource;
	};

	class Shader {
		std::string filepath;
		unsigned int rendererID;
		std::unordered_map<std::string, int> uniformLocationCache;

	public:
		Shader(const std::string& filepath);
		~Shader();
		void bind() const;
		void unbind() const;

		// Set Uniforms
		void setUniform1i(const std::string& name, int value);
		void setUniform1f(const std::string& name, float value);
		void setUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
		void setUniformMat4f(const std::string& name, glm::mat4 matrix);

	private:
		ShaderSource parseShader(const std::string& filepath);
		unsigned int compileShader(unsigned int type, const std::string& source);
		unsigned int createProgram(const std::string& vertexShader, const std::string& fragmentShader);
		int getUniformLocation(const std::string& name);
	};
}


//ShaderSource parseShader(const std::string& filepath);
//unsigned int compileShader(unsigned int type, const std::string& source);
//unsigned int createProgram(const std::string& vertexShader, const std::string& fragmentShader);
//
//
//void deleteProgram();
//
//// Getters
//unsigned int getProgramID();