#pragma once

#include "entity.hpp"
#include <string>

namespace vew
{
	class Component
	{
	public:
		// Called once per frame.
		virtual void update();

		// Called once per frame.
		virtual void lateUpdate();

		// Called once per viewport render.
		virtual void preRenderUpdate();
	};

	// This, when used as a static variable, self-registers the class T as an available component type.
	template <typename T>
	class ComponentRegister
	{
	public:
		ComponentRegister(std::string const & type)
		{
			Entity::registerComponent<T>(type);
		}
	};
}