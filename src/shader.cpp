#include "shader.hpp"
#include <GLES2/gl2.h>

namespace VEW
{
	Shader::Shader(std::string const& vertexCode, std::string const& fragmentCode)
	{
		std::vector<unsigned int> objects;
		objects.push_back(compileObject("vertex", vertexCode));
		objects.push_back(compileObject("fragment", fragmentCode));
		program = linkProgram(objects);
	}

	Shader::~Shader()
	{
	}

	unsigned int Shader::compileObject(std::string const& type, std::string const& code)
	{
		unsigned int glType = 0;
		if (type == "vertex")
		{
			glType = GL_VERTEX_SHADER;
		}
		else if (type == "fragment")
		{
			glType = GL_FRAGMENT_SHADER;
		}
		else
		{
			throw std::runtime_error("Unknown object type '" + type + "', with code:\n" + code + "\n");
		}
		unsigned int object;
		object = glCreateShader(glType);
		char const* shaderCode = code.c_str();
		GLint shaderCodeSize = (GLint)code.size();
		glShaderSource(object, 1, &shaderCode, &shaderCodeSize);
		glCompileShader(object);
		GLint good;
		glGetShaderiv(object, GL_COMPILE_STATUS, &good);
		if (good == GL_FALSE)
		{
			GLint logLength;
			std::string log;
			glGetShaderiv(object, GL_INFO_LOG_LENGTH, &logLength);
			log.resize(logLength);
			glGetShaderInfoLog(object, logLength, 0, &log[0]);
			log.pop_back(); // get rid of \0
			std::string typeString;
			glDeleteShader(object);
			throw std::runtime_error("Error compiling code: " + log + "Code:\n" + code + "\n");
		}
		return object;
	}

	unsigned int Shader::linkProgram(std::vector<unsigned int> const& objects)
	{
		unsigned int program = glCreateProgram();
		for (unsigned int object : objects)
		{
			glAttachShader(program, object);
		}
		glLinkProgram(program);
		GLint good;
		glGetProgramiv(program, GL_LINK_STATUS, &good);
		if (good == GL_FALSE)
		{
			GLint logLength;
			std::string log;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
			log.resize(logLength);
			glGetProgramInfoLog(program, logLength, 0, &log[0]);
			glDeleteProgram(program);
			throw std::runtime_error("Error linking program: " + log);
		}
		return program;
	}
}