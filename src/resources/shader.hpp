#pragma once

#include <math/vector.hpp>
#include <math/matrix.hpp>
#include <string>
#include <map>

namespace vew
{
	class Shader
	{
	public:
		// Constructs a shader from vertex and shader code.
		Shader(std::string const & vertexCode, std::string const & fragmentCode);

		// Destructs the shader.
		~Shader();

		// Returns the location of the named uniform.
		int getUniformLocation(std::string const & name) const;

		// Sets the value of the uniform.
		void setUniform(int location, int value) const;

		// Sets the value of the uniform.
		void setUniform(int location, float value) const;

		// Sets the value of the uniform.
		void setUniform(int location, Vector2i value) const;

		// Sets the value of the uniform.
		void setUniform(int location, Vector2f value) const;

		// Sets the value of the uniform.
		void setUniform(int location, Vector3f value) const;

		// Sets the value of the uniform.
		void setUniform(int location, Vector4f value) const;

		// Sets the value of the uniform.
		void setUniform(int location, Matrix44f value) const;

		// Internal to vew. Activates the shader. Called by Model.
		void activate();

	private:
		unsigned int program;
		std::map<std::string, int> uniformLocations;
	};
}