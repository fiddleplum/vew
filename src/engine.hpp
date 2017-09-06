#pragma once

#include "vector.hpp"
#include <string>
#include <vector>
#include <set>

namespace vew
{
	class Viewport;
	class Entity;
	
	class Engine
	{
	public:
		Engine();

		~Engine();

		void render();

		void printMessage(std::string const& message);

		Viewport * addViewport();

		void removeViewport(Viewport * viewport);

		Entity * addEntity();

		void removeEntity(Entity * entity);

	private:
		Vector2d canvasSize;

		std::vector<Viewport *> viewports;
		std::set<Entity *> entities;
	};
}