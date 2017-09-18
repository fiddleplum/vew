#include <components/component.hpp>
#include <emscripten/bind.h>

namespace vew
{
	void Component::update()
	{
	}

	void Component::lateUpdate()
	{
	}

	void Component::preRenderUpdate()
	{
	}
}

// Binding Code
EMSCRIPTEN_BINDINGS(vew_Component)
{
	emscripten::class_<vew::Component>("Component")
	.constructor<>()
	;
}