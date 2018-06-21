#include "Shader.hpp"
#include<fstream>
#include<sstream>
#include<GL\glew.h>
#include<iostream>


namespace toti {
	struct Shader::ShaderSource {
		std::string vertexSource;
		std::string fragmentSource;
	};

	Shader::Shader() {
		ShaderSource source = parseShader("Resources/Shaders/Basic.shader");
		programID = createProgram(source.vertexSource, source.fragmentSource);
	}

	//**********

	Shader::ShaderSource Shader::parseShader(const std::string& filepath) {
		enum class ShaderType {
			NONE = -1, VERTEX = 0, FRAGMENT = 1
		};

		std::ifstream stream(filepath);
		std::string line;
		std::stringstream ss[2];
		ShaderType type = ShaderType::NONE;

		while (getline(stream, line)) {
			if (line.find("#shader") != std::string::npos) {
				if (line.find("vertex") != std::string::npos)
					type = ShaderType::VERTEX;
				else if (line.find("fragment") != std::string::npos)
					type = ShaderType::FRAGMENT;
			}
			else {
				ss[(int)type] << line << '\n';
			}
		}

		return{ ss[0].str(), ss[1].str() };
	}

	unsigned int Shader::compileShader(unsigned int type, const std::string& source) {
		unsigned int id = glCreateShader(type);
		const char* src = source.c_str();
		glShaderSource(id, 1, &src, nullptr);
		glCompileShader(id);

		// Error Checking
		int result;
		glGetShaderiv(id, GL_COMPILE_STATUS, &result);
		if (!result) {
			int length;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
			char* message = (char*)alloca(length * sizeof(char));
			glGetShaderInfoLog(id, length, &length, message);
			std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << std::endl;
			std::cout << message << std::endl;
			glDeleteShader(id);
			return 0;
		}

		return id;
	}

	unsigned int Shader::createProgram(const std::string& vertexShader, const std::string& fragmentShader) {
		unsigned int program = glCreateProgram();
		unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
		unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

		glAttachShader(program, vs);
		glAttachShader(program, fs);
		glLinkProgram(program);
		glValidateProgram(program);

		glDeleteShader(vs);
		glDeleteShader(fs);

		return program;
	}

	void Shader::deleteProgram() {
		glDeleteProgram(programID);
	}

	// Getters
	unsigned int Shader::getProgramID() {
		return programID;
	}
}