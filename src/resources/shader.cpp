#include <resources/shader.hpp>
#include <GLES2/gl2.h>
#include <vector>

namespace vew
{
	int compileObject(std::string const & type, std::string const & code);
	int linkProgram(std::vector<int> const & objects);
	void populateUniformMapping(std::map<std::string, int> & uniforms, int program);

	Shader::Shader(std::string const & vertexCode, std::string const & fragmentCode)
	{
		std::vector<int> objects;
		objects.push_back(compileObject("vertex", vertexCode));
		objects.push_back(compileObject("fragment", fragmentCode));
		program = linkProgram(objects);
		for (int object : objects)
		{
			glDetachShader(program, object);
			glDeleteShader(object);
		}
		populateUniformMapping(uniformLocations, program);
	}

	Shader::~Shader()
	{
		glDeleteProgram(program);
	}

	int Shader::getUniformLocation(std::string const & name) const
	{
		auto iter = uniformLocations.find(name);
		if (iter == uniformLocations.end())
		{
			return -1;
		}
		return iter->second;
	}

	void Shader::setUniform(int location, int value) const
	{
		glUniform1i(location, value);
	}

	void Shader::setUniform(int location, float value) const
	{
		glUniform1f(location, value);
	}

	void Shader::setUniform(int location, Vector2i value) const
	{
		glUniform2iv(location, 1, value.ptr());
	}

	void Shader::setUniform(int location, Vector2f value) const
	{
		glUniform2fv(location, 1, value.ptr());
	}

	void Shader::setUniform(int location, Vector3f value) const
	{
		glUniform3fv(location, 1, value.ptr());
	}

	void Shader::setUniform(int location, Vector4f value) const
	{
		glUniform4fv(location, 1, value.ptr());
	}

	void Shader::setUniform(int location, Matrix44f value) const
	{
		glUniformMatrix4fv(location, 1, false, value.ptr());
	}

	void Shader::activate()
	{
		glUseProgram(program);
	}

	int compileObject(std::string const & type, std::string const & code)
	{
		int glType = 0;
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
		int object;
		object = glCreateShader(glType);
		char const * shaderCode = code.c_str();
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

	int linkProgram(std::vector<int> const & objects)
	{
		int program = glCreateProgram();
		for (int object : objects)
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

	void populateUniformMapping(std::map<std::string, int> & uniformLocations, int program)
	{
		GLint numVariables;
		GLint maxNameSize;
		std::string name;
		glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &numVariables);
		glGetProgramiv(program, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxNameSize);
		for (int i = 0; i < numVariables; i++)
		{
			GLsizei nameSize;
			GLint glSize;
			GLenum glType;
			name.resize(maxNameSize);
			glGetActiveUniform(program, i, maxNameSize, &nameSize, &glSize, &glType, &name[0]);
			name.resize(nameSize);
			int location = glGetUniformLocation(program, name.c_str());
			uniformLocations[name] = location;
		}
	}
}