#pragma once

#include "vector.hpp"
#include <string>

namespace vew
{
	class Engine
	{
	public:
		Engine();

		~Engine();

		void render();

		void printMessage(std::string const& message);

	private:
		Vector2d canvasSize;
	};
}