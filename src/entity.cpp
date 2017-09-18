#include <entity.hpp>
#include <components/component.hpp>
#include <emscripten/bind.h>
#include <emscripten/emscripten.h>
#include <iostream>

namespace vew
{
	// Creates a singleton of component types for the entity's component factory.
	std::map<std::string, std::function<Component *()>> & componentTypeFunctors()
	{
		static std::map<std::string, std::function<Component *()>> _componentTypeFunctors;
		return _componentTypeFunctors;
	}

	Entity::Entity()
	{
		position = Vector3d::zero();
		orientation = Quaterniond::identity();
		parent = nullptr;
	}

	Vector3d Entity::getPosition() const
	{
		return position;
	}

	void Entity::setPosition(Vector3d position)
	{
		this->position = position;
	}

	Quaterniond Entity::getOrientation() const
	{
		return orientation;
	}

	void Entity::setOrientation(Quaterniond orientation)
	{
		this->orientation = orientation;
	}

	Entity * Entity::getParent() const
	{
		return parent;
	}

	void Entity::setParent(Entity * parent)
	{
		this->parent = parent;
	}

	Component * Entity::addComponent(std::string const & type)
	{
		auto iter = componentTypeFunctors().find(type);
		if (iter != componentTypeFunctors().end())
		{
			Component * component = iter->second();
			components.insert(component);
			return component;
		}
		std::cout << "Component type " << type << " not found." << std::endl;
		return nullptr;
	}

	void Entity::removeComponent(Component * component)
	{
		auto iter = components.find(component);
		if (iter != components.end())
		{
			components.erase(iter);
			delete component;
			return;
		}
		std::cout << "Could not find component." << std::endl;
	}

	void Entity::listComponentTypes()
	{
		std::cout << componentTypeFunctors().size() << std::endl;
		std::vector<std::string> componentTypes;
		for (auto pair : componentTypeFunctors())
		{
			std::cout << pair.first << std::endl;
			componentTypes.push_back(pair.first);
		}
	}

	void Entity::registerComponent(std::string const & type, std::function<Component *()> newComponentFunctor)
	{
		componentTypeFunctors()[type] = newComponentFunctor;
	}
}

// Binding Code
EMSCRIPTEN_BINDINGS(vew_Entity)
{
	emscripten::register_vector<std::string>("VectorString");
	emscripten::class_<vew::Entity>("Entity")
		.function("getPosition", &vew::Entity::getPosition)
		.function("setPosition", &vew::Entity::setPosition)
		.function("getOrientation", &vew::Entity::getOrientation)
		.function("setOrientation", &vew::Entity::setOrientation)
		.function("getParent", &vew::Entity::getParent, emscripten::allow_raw_pointers())
		.function("setParent", &vew::Entity::setParent, emscripten::allow_raw_pointers())
		.function("addComponent", &vew::Entity::addComponent, emscripten::allow_raw_pointers())
		.function("removeComponent", &vew::Entity::removeComponent, emscripten::allow_raw_pointers())
		.class_function("listComponentTypes", &vew::Entity::listComponentTypes);
}