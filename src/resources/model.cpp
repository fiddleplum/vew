#include <resources/model.hpp>
#include <emscripten/bind.h>
#include <emscripten/emscripten.h>

namespace vew
{
	Model::Model()
	{
	}

	Model::~Model()
	{
	}

	void Model::setMesh(Mesh * mesh_)
	{
		mesh = mesh_;
	}

	void Model::setShader(Shader * shader_)
	{
		shader = shader_;
	}

	void Model::setUniformsFunction(std::function<void()> uniformsFunction_)
	{
		uniformsFunction = uniformsFunction_;
	}

	void Model::render()
	{
		if (shader != nullptr)
		{
			shader->activate();
			if (uniformsFunction)
			{
				uniformsFunction();
			}
		}
		if (mesh != nullptr)
		{
			mesh->render();
		}
	}
}