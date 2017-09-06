#pragma once

#include "vector.hpp"
#include "quaternion.hpp"
#include <string>
#include <map>
#include <set>

namespace vew
{
	class Component;

	class Entity
	{
	public:
		Entity();

		Vector3d getPosition() const;

		void setPosition(Vector3d position);

		Quaterniond getOrientation() const;

		void setOrientation(Quaterniond orientation);

		Entity * getParent() const;

		void setParent(Entity * parent);

		Component * addComponent(std::string const & type);

		void removeComponent(Component * component);

		static void registerComponent(std::string const & type, std::function<Component *()> const & newFunctor);

	private:
		Vector3d position;
		Quaterniond orientation;
		Entity * parent;
		std::set<Component *> components;

		static std::map<std::string, std::function<Component *()>> componentTypeFunctors;
	};
}