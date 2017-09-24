#include <math/vector.hpp>
#include <emscripten/bind.h>
#include <emscripten/emscripten.h>

// Binding Code
EMSCRIPTEN_BINDINGS(vew_Vector3d)
{
	emscripten::value_array<vew::Vector3d>("Vector3d")
		.element(emscripten::index<0>())
		.element(emscripten::index<1>())
		.element(emscripten::index<2>());
}

// Binding Code
EMSCRIPTEN_BINDINGS(vew_Vector2d)
{
	emscripten::value_array<vew::Vector2d>("Vector2d")
	.element(emscripten::index<0>())
	.element(emscripten::index<1>());
}