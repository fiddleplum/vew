#include "engine.hpp"
#include <SDL/SDL.h>
#include <iostream>

namespace VEW
{
	Engine::Engine()
	{
		int result = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER);
		if (result != 0)
		{
			std::cerr << "Could not initialize SDL: " << SDL_GetError() << std::endl;
			return;
		}
		SDL_SetVideoMode(800, 600, 0, SDL_OPENGL);
		std::cout << "Success" << std::endl;
	}

	Engine::~Engine()
	{
	}
}