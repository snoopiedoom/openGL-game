#pragma once

//this whole thing basically maintains the elements of the vertex buffer, in other words,
//layout of the actual buffer, connecting/binding the vertex buffer with the vertex layout
//is done in the vertexArray.h

#include <vector>
#include <GL/glew.h>

#include "renderer.h"

struct VertexBufferElement
{
	//parameters for the glVertexAttribArray
	unsigned int count;
	unsigned int type;
	unsigned char normalized;

	static unsigned int getSizeOfType(unsigned int type) //returns appropriate type size to be used as a parameter
	{ //in case I were to use more types, this can be easily expanded upon
		switch (type)
		{
			case GL_FLOAT:			return 4;
			case GL_UNSIGNED_INT:	return 4;
			case GL_UNSIGNED_BYTE:  return 1;
		}
		ASSERT(false);
		return 0;
	}
};

class VertexBufferLayout
{
private:
	std::vector<VertexBufferElement> m_Elements;
	unsigned int m_Stride;
public:
	VertexBufferLayout() {
		m_Stride = 0;
	}

	template<typename T>
	void push(unsigned int count)
	{
		static_assert(false);
	}

	template<>
	void push<float>(unsigned int count) //cannot have a negative count...
	{
		m_Elements.push_back({ GL_FLOAT , count , GL_FALSE });
		m_Stride += count * VertexBufferElement::getSizeOfType(GL_FLOAT);
	}

	template<>
	void push<unsigned int>(unsigned int count)
	{
		m_Elements.push_back({ GL_UNSIGNED_INT , count , GL_FALSE });
		m_Stride += count * VertexBufferElement::getSizeOfType(GL_UNSIGNED_INT);
	}

	template<>
	void push<unsigned char>(unsigned int count) //unsigned char - basically bytes
	{
		m_Elements.push_back({ GL_UNSIGNED_BYTE , count , GL_TRUE }); //we keeping those
		m_Stride += count * VertexBufferElement::getSizeOfType(GL_UNSIGNED_BYTE);
	}


	inline const std::vector<VertexBufferElement> getElements() const { return m_Elements; }
	inline unsigned int getStride() const { return m_Stride; }
};