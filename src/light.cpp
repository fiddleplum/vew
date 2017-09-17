#include "light.hpp"

namespace vew
{
	Vector3d Light::getColor() const
	{
		return color;
	}

	void Light::setColor(Vector3d color_)
	{
		color = color_;
	}
}

// Binding Code
EMSCRIPTEN_BINDINGS(vew_Light)
{
	emscripten::class_<vew::Light, emscripten::base<vew::Component>>("Light")
		.constructor<>()
		.function("getColor", &vew::Light::getColor)
		.function("setColor", &vew::Light::setColor);
}