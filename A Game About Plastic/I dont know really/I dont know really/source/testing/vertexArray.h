#pragma once

#include "vertexBuffer.h"
#include "vertexBufferLayout.h"

class VertexArray //sets everything up on the openGL side
{
private:
	unsigned int m_RendererID;
public:
	VertexArray();
	~VertexArray();

	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
	void Bind() const;
	void UnBind() const;
};