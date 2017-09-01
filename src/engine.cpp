#include "engine.hpp"
#include <SDL/SDL.h>
#include <emscripten/bind.h>
#include <emscripten/emscripten.h>
#include <GLES2/gl2.h>
#include <iostream>

namespace vew
{
	Engine::Engine()
	{
		int canvasWidth;
		int canvasHeight;
		emscripten_get_canvas_size(&canvasWidth, &canvasHeight, nullptr);
		canvasSize = {(double)canvasWidth, (double)canvasHeight};

		int result = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER);
		if (result != 0)
		{
			std::cerr << "Could not initialize SDL: " << SDL_GetError() << std::endl;
			return;
		}
		SDL_SetVideoMode(canvasWidth, canvasHeight, 0, SDL_OPENGL);
		std::cout << "Success" << std::endl;
	}

	Engine::~Engine()
	{
		std::cout << "Deleted." << std::endl;
		SDL_Quit();
	}

	void Engine::render()
	{
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		glViewport(0, 0, canvasSize[0], canvasSize[1]);
		glClear(GL_COLOR_BUFFER_BIT);
		SDL_GL_SwapBuffers();
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
	.constructor<>()
	.function("render", &vew::Engine::render)
	.function("printMessage", &vew::Engine::printMessage);
}