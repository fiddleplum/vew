#pragma once

#include <vector>
#include <map>

namespace vew
{
	class Mesh
	{
	public:
		// Constructs an empty mesh.
		Mesh();

		// Destructor.
		~Mesh();

		// Sets the number of consecutive indices that make a single primitive. 1 for points, 2 for lines, and 3 for triangles.
		void setNumIndicesPerPrimitive(int numIndices);

		// Sets the vertex component of the given index. The component index is used for the glsl layout attribute specifier. If instanced, then each value for this component in the vertices will be per instance rather than per vertex.
		void setVertexComponent(int componentIndex, int numDimensions, int byteOffsetInVertex, int verticesIndex);

		// Sets the vertices at a given index.
		void setVertices(int index, std::vector<float> const & vertices, int byteSizeOfVertex, bool instanced);

		// Sets the indices of a single instance.
		void setIndices(std::vector<int> const & indices);

		// Sets the number of instances to render. Not supported if using GL ES 2.0.
		void setNumInstances(int numInstances);

		// Internal to view. Renders the Mesh. Called by Model.
		void render() const;

	private:
		int numIndicesPerPrimitive;
		int numIndicesInInstance;
		int numInstances;
		int glMode;
#ifdef GL_ES_VERSION_3_0
		unsigned int vertexArrayObject;
		std::map<int, unsigned int> vertexBufferObjects;
#else
		struct VertexComponent
		{
			int numDimensions;
			int byteOffsetInVertex;
		};
		struct VertexBufferObject
		{
			unsigned int buffer;
			int byteSizeOfVertex;
			std::vector<VertexComponent> components;
		};
		std::map<int, VertexBufferObject> vertexBufferObjects;
#endif
		unsigned int indexBufferObject;
	};
}