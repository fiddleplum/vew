#include "quaternion.hpp"
#include <emscripten/bind.h>
#include <emscripten/emscripten.h>
#include <string>

namespace vew
{
	template <typename T>
	std::string toString(Quaternion<T> const & v)
	{
		return std::string("(") + std::to_string(v[0]) + ", " + std::to_string(v[1]) + ", " + std::to_string(v[2]) + ", " + std::to_string(v[3]) + ")";
	}
}

// Binding Code
EMSCRIPTEN_BINDINGS(vew_Quaterniond)
{
	emscripten::class_<vew::Quaterniond>("Quaterniond")
		.constructor<>()
		.constructor<double, double, double, double>()
		.function("get", emscripten::select_overload<double(int) const>(&vew::Quaterniond::operator[]))
		.function("set", emscripten::select_overload<double &(int)>(&vew::Quaterniond::operator[]))
		.function("toString", emscripten::select_overload<std::string(vew::Quaterniond const &)>(&vew::toString<double>));
}