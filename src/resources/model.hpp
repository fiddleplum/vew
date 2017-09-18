#include <resources/mesh.hpp>
#include <resources/shader.hpp>
#include <functional>

namespace vew
{
	class Model final
	{
	public:
		Model();

		~Model();

		void setMesh(Mesh * mesh);

		void setShader(Shader * shader);

		void setUniformsFunction(std::function<void ()> uniformsFunction);

		void render();

	private:
		Mesh * mesh = nullptr;
		Shader * shader = nullptr;
		std::function<void ()> uniformsFunction;
	};
}