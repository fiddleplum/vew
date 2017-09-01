#pragma once

#include "vector.hpp"
#include "matrix.hpp"
#include <string>
#include <map>

namespace vew
{
	class Shader
	{
	public:
		Shader(std::string const& vertexCode, std::string const& fragmentCode);
		~Shader();

		int getUniformLocation(std::string const& name) const;

		void setUniform(int location, int value) const;
		void setUniform(int location, float value) const;
		void setUniform(int location, Vector2i value) const;
		void setUniform(int location, Vector2f value) const;
		void setUniform(int location, Vector3f value) const;
		void setUniform(int location, Vector4f value) const;
		void setUniform(int location, Matrix44f value) const;

	private:
		unsigned int program;
		std::map<std::string, int> uniformLocations;
	};
}