#include "component.hpp"
#include <emscripten/bind.h>

// Binding Code
EMSCRIPTEN_BINDINGS(vew_Component)
{
	emscripten::class_<vew::Component>("Component")
	.constructor<>()
	;
}