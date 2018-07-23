#include "Shader.hpp"
#include<fstream>
#include<sstream>
#include<GL\glew.h>
#include<iostream>
#include"Engine\Util\HelperFuntions.hpp"

namespace toti {

	Shader::Shader(const std::string& filepath) : filepath(filepath), rendererID(0) {
		ShaderSource source = parseShader(filepath);
		rendererID = createProgram(source.vertexSource, source.fragmentSource);
	}
	Shader::~Shader() {
		callGL(glDeleteProgram(rendererID));
	}



	void Shader::bind() const {
		callGL(glUseProgram(rendererID));
	}
	void Shader::unbind() const {
		callGL(glUseProgram(0));
	}


	ShaderSource Shader::parseShader(const std::string& filepath) {
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
		callGL(glShaderSource(id, 1, &src, nullptr));
		callGL(glCompileShader(id));

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

		callGL(glAttachShader(program, vs));
		callGL(glAttachShader(program, fs));
		callGL(glLinkProgram(program));
		callGL(glValidateProgram(program));

		callGL(glDeleteShader(vs));
		callGL(glDeleteShader(fs));

		return program;
	}

	void Shader::setUniform1i(const std::string& name, int value) {
		callGL(glUniform1i(getUniformLocation(name), value));
	}
	void Shader::setUniform1f(const std::string& name, float value) {
		callGL(glUniform1f(getUniformLocation(name), value));
	}
	void Shader::setUniform4f(const std::string& name, float v0, float v1, float v2, float v3) {
		callGL(glUniform4f(getUniformLocation(name), v0, v1, v2, v3));
	}

	void Shader::setUniformMat4f(const std::string& name, glm::mat4 matrix) {
		callGL(glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
	}

	int Shader::getUniformLocation(const std::string& name) {
		if (uniformLocationCache.find(name) != uniformLocationCache.end())
			return uniformLocationCache[name];

		int location = glGetUniformLocation(rendererID, name.c_str());
		if (location == -1)
			std::cout << "WARNING: Uniform '" << name << "' doesn't exist!" << std::endl;
		
		uniformLocationCache[name] = location;
		return location;
	}
}