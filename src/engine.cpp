#include "engine.hpp"
#include "viewport.hpp"
#include "entity.hpp"
#include "vector.hpp"
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

		int result = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER);
		if (result != 0)
		{
			std::cerr << "Could not initialize SDL: " << SDL_GetError() << std::endl;
			return;
		}
		SDL_SetVideoMode(canvasWidth, canvasHeight, 0, SDL_OPENGL);
	}

	Engine::~Engine()
	{
		SDL_Quit();
	}

	Viewport * Engine::addViewport()
	{
		Viewport * viewport = new Viewport();
		viewport->setCanvasSize(canvasSize);
		viewports.push_back(viewport);
		return viewport;
	}

	void Engine::removeViewport(Viewport * viewport)
	{
		for (int i = 0; i < viewports.size(); i++)
		{
			if (viewports[i] == viewport)
			{
				viewports.erase(viewports.begin() + i);
				delete viewport;
				return;
			}
		}
		std::cerr << "Viewport not found." << std::endl;
	}

	Entity * Engine::addEntity()
	{
		Entity * entity = new Entity();
		entities.insert(entity);
		return entity;
	}

	void Engine::removeEntity(Entity * entity)
	{
		auto iter = entities.find(entity);
		if (iter != entities.end())
		{
			entities.erase(iter);
			delete entity;
			return;
		}
		std::cerr << "Entity not found." << std::endl;
	}

	void Engine::update()
	{
		// Check the canvas size.
		int canvasWidth;
		int canvasHeight;
		emscripten_get_canvas_size(&canvasWidth, &canvasHeight, nullptr);
		if (canvasSize[0] != (double)canvasWidth || canvasSize[1] != (double)canvasHeight)
		{
			canvasSize = {(double)canvasWidth, (double)canvasHeight};
			for (auto viewport : viewports)
			{
				viewport->setCanvasSize(canvasSize);
			}
		}

		// Clear the canvas.
		glViewport(0, 0, canvasSize[0], canvasSize[1]);
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Render the viewports.
		for (auto viewport : viewports)
		{
			viewport->render();
		}

		// Swap the buffers.
		SDL_GL_SwapBuffers();
	}
}

// Binding Code
EMSCRIPTEN_BINDINGS(vew_Engine)
{
	emscripten::class_<vew::Engine>("Engine")
		.function("addViewport", &vew::Engine::addViewport, emscripten::allow_raw_pointers())
		.function("removeViewport", &vew::Engine::removeViewport, emscripten::allow_raw_pointers())
		.function("addEntity", &vew::Engine::addEntity, emscripten::allow_raw_pointers())
		.function("removeEntity", &vew::Engine::removeEntity, emscripten::allow_raw_pointers());
}