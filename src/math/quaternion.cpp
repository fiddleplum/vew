#include <math/quaternion.hpp>
#include <emscripten/bind.h>
#include <emscripten/emscripten.h>

// Binding Code
EMSCRIPTEN_BINDINGS(vew_Quaterniond)
{
	emscripten::value_array<vew::Quaterniond>("Quaterniond")
	.element(emscripten::index<0>())
	.element(emscripten::index<1>())
	.element(emscripten::index<2>())
	.element(emscripten::index<3>());
}