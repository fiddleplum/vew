#include "rect.hpp"
#include <emscripten/bind.h>
#include <emscripten/emscripten.h>
#include <string>

namespace vew
{
	template <typename T>
	std::string toString(Interval<2, T> const& v)
	{
		return std::string("(") + std::to_string(v.min[0]) + ", " + std::to_string(v.min[1]) + ", " + std::to_string(v.max[0]) + ", " + std::to_string(v.max[1]) + ")";
	}
}

// Binding Code
EMSCRIPTEN_BINDINGS(vew_Rectd)
{
	emscripten::class_<vew::Rectd>("Rectd")
	.constructor<>()
	.property("min", &vew::Rectd::getMin, &vew::Rectd::setMin)
	.property("max", &vew::Rectd::getMax, &vew::Rectd::setMax)
	.function("toString", emscripten::select_overload<std::string(vew::Rectd const&)>(&vew::toString<double>));
}