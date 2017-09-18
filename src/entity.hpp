#pragma once

#include <math/vector.hpp>
#include <math/quaternion.hpp>
#include <string>
#include <map>
#include <set>
#include <iostream>

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

		static void listComponentTypes();

		// Used by ComponentRegister to self-register component types.
		template <typename T>
		static void registerComponent(std::string const & type);

	private:
		static void registerComponent(std::string const & type, std::function<Component *()> newComponentFunctor);

		Vector3d position;
		Quaterniond orientation;
		Entity * parent;
		std::set<Component *> components;
	};

	// Template implementation

	template <typename T>
	void Entity::registerComponent(std::string const & type)
	{
		std::cout << "Registering " << type << std::endl;
		registerComponent(type, []() -> T * {
			return new T();
		});
	}
}