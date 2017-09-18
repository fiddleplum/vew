#include <resources/mesh.hpp>
#include <GLES2/gl2.h>

namespace vew
{
	Mesh::Mesh()
	{
		numIndicesPerPrimitive = 3;
		numIndicesInInstance = 0;
		numInstances = 1;
		glMode = GL_TRIANGLES;
#ifdef GL_ES_VERSION_3_0
		glGenVertexArrays(1, &vertexArrayObject);
#endif
		glGenBuffers(1, &indexBufferObject);
	}

	Mesh::~Mesh()
	{
		for (auto && pair : vertexBufferObjects)
		{
#ifdef GL_ES_VERSION_3_0
			glDeleteBuffers(1, &pair.second);
#else
			glDeleteBuffers(1, &pair.second.buffer);
#endif
		}
#ifdef GL_ES_VERSION_3_0
		glDeleteVertexArrays(1, &vertexArrayObject);
#endif
		glDeleteBuffers(1, &indexBufferObject);
	}

	void Mesh::setNumIndicesPerPrimitive(int numIndices)
	{
		numIndicesPerPrimitive = numIndices;
		switch (numIndices)
		{
		case 1:
			glMode = GL_POINTS;
			break;
		case 2:
			glMode = GL_LINES;
			break;
		case 3:
			glMode = GL_TRIANGLES;
			break;
		default:
			throw std::runtime_error("Error: Wrong number of indices per primitive. ");
		}
	}

	void Mesh::setVertexComponent(int componentIndex, int numDimensions, int byteOffsetInVertex, int verticesIndex)
	{
#ifdef GL_ES_VERSION_3_0
		glBindVertexArray(vertexArrayObject);
		glEnableVertexAttribArray(componentIndex);
		glVertexAttribFormat(componentIndex, numDimensions, GL_FLOAT, GL_FALSE, byteOffsetInVertex);
		glVertexAttribBinding(componentIndex, verticesIndex);
#else
		VertexBufferObject & vbo = vertexBufferObjects[verticesIndex];
		if (vbo.components.size() <= componentIndex)
		{
			vbo.components.resize(componentIndex);
		}
		vbo.components[componentIndex].numDimensions = numDimensions;
		vbo.components[componentIndex].byteOffsetInVertex = byteOffsetInVertex;
#endif
	}

	void Mesh::setVertices(int index, std::vector<float> const & vertices, int byteSizeOfVertex, bool instanced)
	{
		auto it = vertexBufferObjects.find(index);
		if (vertices.size() > 0 && byteSizeOfVertex > 0)
		{
#ifdef GL_ES_VERSION_3_0
			unsigned int vertexBufferObject;
			if (it == vertexBufferObjects.end())
			{
				glBindVertexArray(vertexArrayObject);
				glGenBuffers(1, &vertexBufferObject);
				glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject); // Even though this isn't required, my video card has a bug which does require it for glBindVertexBuffer.
				glBindVertexBuffer(index, vertexBufferObject, 0, byteSizeOfVertex);
				glVertexBindingDivisor(index, instanced ? 1 : 0);
				vertexBufferObjects.insert(std::pair<int, int>(index, vertexBufferObject));
			}
			else
			{
				vertexBufferObject = it->second;
			}
			glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
#else
			unsigned int buffer;
			if (it == vertexBufferObjects.end())
			{
				VertexBufferObject vertexBufferObject;
				glGenBuffers(1, &vertexBufferObject.buffer);
				glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject.buffer); // Even though this isn't required, my video card has a bug which does require it for glBindVertexBuffer.
				vertexBufferObjects.insert(std::pair<int, VertexBufferObject>(index, vertexBufferObject));
				buffer = vertexBufferObject.buffer;
			}
			else
			{
				buffer = it->second.buffer;
			}
			glBindBuffer(GL_ARRAY_BUFFER, buffer);
#endif
			glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), (void const *)&vertices[0], GL_STATIC_DRAW);
		}
		else if (it != vertexBufferObjects.end())
		{
			auto vertexBufferObject = it->second;
			vertexBufferObjects.erase(it);
#ifdef GL_ES_VERSION_3_0
			glBindVertexArray(vertexArrayObject);
			glDisableVertexAttribArray(index);
			glBindVertexBuffer(index, 0, 0, 0);
			glDeleteBuffers(1, &vertexBufferObject);
#else
			glDeleteBuffers(1, &vertexBufferObject.buffer);
#endif
		}
	}

	void Mesh::setIndices(std::vector<int> const & indices)
	{
		numIndicesInInstance = (int)indices.size();
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), (void const *)&indices[0], GL_STATIC_DRAW);
	}

	void Mesh::setNumInstances(int numInstances_)
	{
		numInstances = numInstances_;
	}

	void Mesh::render() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject);
#ifdef GL_ES_VERSION_3_0
		glBindVertexArray(vertexArrayObject);
		glDrawElementsInstanced(glMode, numIndicesInInstance, GL_UNSIGNED_INT, 0, numInstances);
		glBindVertexArray(0);
#else
		for (int vboI = 0; vboI < vertexBufferObjects.size(); vboI++)
		{
			VertexBufferObject const & vertexBufferObject = vertexBufferObjects.at(vboI);
			glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject.buffer);
			for (unsigned int vcI = 0; vcI < vertexBufferObject.components.size(); vcI++)
			{
				VertexComponent const & vertexComponent = vertexBufferObject.components.at(vcI);
				glVertexAttribPointer(vcI, vertexComponent.numDimensions, GL_FLOAT, false, vertexBufferObject.byteSizeOfVertex, (void *)vertexComponent.byteOffsetInVertex);
				glEnableVertexAttribArray(vcI);
			}
		}
		glDrawElements(glMode, numIndicesInInstance, GL_UNSIGNED_INT, 0);
#endif
	}
}