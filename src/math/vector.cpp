#include <math/vector.hpp>
#include <emscripten/bind.h>
#include <emscripten/emscripten.h>
#include <string>

namespace vew
{
	template <typename T>
	std::string toString(Vector<2, T> const & v)
	{
		return std::string("(") + std::to_string(v[0]) + ", " + std::to_string(v[1]) + ")";
	}

	template <typename T>
	std::string toString(Vector<3, T> const & v)
	{
		return std::string("(") + std::to_string(v[0]) + ", " + std::to_string(v[1]) + ", " + std::to_string(v[2]) + ")";
	}
}

// Binding Code
EMSCRIPTEN_BINDINGS(vew_Vector3d)
{
	emscripten::class_<vew::Vector3d>("Vector3d")
		.constructor<>()
		.function("get", emscripten::select_overload<double(int) const>(&vew::Vector3d::operator[]))
		.function("set", emscripten::select_overload<double &(int)>(&vew::Vector3d::operator[]))
		.function("toString", emscripten::select_overload<std::string(vew::Vector3d const &)>(&vew::toString<double>));
}

// Binding Code
EMSCRIPTEN_BINDINGS(vew_Vector2d)
{
	emscripten::class_<vew::Vector2d>("Vector2d")
		.constructor<>()
		.function("get", emscripten::select_overload<double(int) const>(&vew::Vector2d::operator[]))
		.function("set", emscripten::select_overload<double &(int)>(&vew::Vector2d::operator[]))
		.function("toString", emscripten::select_overload<std::string(vew::Vector2d const &)>(&vew::toString<double>));
}