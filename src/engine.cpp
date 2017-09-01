#include "engine.hpp"
#include <SDL/SDL.h>
#include <emscripten/bind.h>
#include <iostream>

namespace vew
{
	Engine::Engine(unsigned int width, unsigned int height)
	{
		int result = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER);
		if (result != 0)
		{
			std::cerr << "Could not initialize SDL: " << SDL_GetError() << std::endl;
			return;
		}
		// SDL_SetVideoMode(width, height, 0, SDL_OPENGL);
		std::cout << "Success" << std::endl;
	}

	Engine::~Engine()
	{
		std::cout << "Deleted." << std::endl;
		SDL_Quit();
	}

	void Engine::printMessage(std::string const& message)
	{
		std::cout << message << std::endl;
	}
}

// Binding Code
EMSCRIPTEN_BINDINGS(vew)
{
	emscripten::class_<vew::Engine>("Engine")
	.constructor<unsigned int, unsigned int>()
	.function("printMessage", &vew::Engine::printMessage)
	;
}