#include "engine.hpp"
#include <emscripten/bind.h>
#include <emscripten/emscripten.h>

vew::Engine * engine = nullptr;

vew::Engine * getEngine()
{
	return engine;
}

void loop()
{
	engine->update();
}

int main()
{
	engine = new vew::Engine();
	emscripten_set_main_loop(loop, 0, 0);
	EM_ASM(initialize());
	return 0;
}

// Binding Code
EMSCRIPTEN_BINDINGS(vew_main)
{
	function("getEngine", &getEngine, emscripten::allow_raw_pointers());
}