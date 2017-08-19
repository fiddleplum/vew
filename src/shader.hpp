#pragma once

#include <string>
#include <vector>

namespace VEW
{
	class Shader
	{
	public:
		Shader(std::string const& vertexCode, std::string const& fragmentCode);
		~Shader();

	private:
		static unsigned int compileObject(std::string const& type, std::string const& code);
		static unsigned int linkProgram(std::vector<unsigned int> const& objects);

		unsigned int program;
	};
}