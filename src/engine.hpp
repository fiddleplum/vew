#pragma once

#include <math/vector.hpp>
#include <resources/resource_cache.hpp>
#include <resources/shader.hpp>
#include <vector>
#include <set>

namespace vew
{
	class Viewport;
	class Entity;

	class Engine final
	{
	public:
		Engine();

		~Engine();

		Viewport * addViewport();

		void removeViewport(Viewport * viewport);

		Entity * addEntity();

		void removeEntity(Entity * entity);

		void addShader(std::string const & name);

		void addTexture(std::string const & name);

		void addMaterial(std::string const & name);

		void addMesh(std::string const & name);

		void update();

	private:
		std::vector<Viewport *> viewports;
		std::set<Entity *> entities;
		ResourceCache<Shader> shaders;

		Vector2d canvasSize;
	};
}