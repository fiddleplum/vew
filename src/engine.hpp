#pragma once

#include <string>

namespace vew
{
	class Engine
	{
	public:
		Engine(unsigned int width, unsigned int height);

		~Engine();

		void printMessage(std::string const& message);

	private:
	};
}