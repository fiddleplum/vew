#pragma once

#include "vector.hpp"
#include <vector>
#include <set>

namespace vew
{
	class Viewport;
	class Entity;

	final class Engine
	{
	public:
		Engine();

		~Engine();

		Viewport * addViewport();

		void removeViewport(Viewport * viewport);

		Entity * addEntity();

		void removeEntity(Entity * entity);

		void update();

	private:
		std::vector<Viewport *> viewports;
		std::set<Entity *> entities;
		Vector2d canvasSize;
	};
}