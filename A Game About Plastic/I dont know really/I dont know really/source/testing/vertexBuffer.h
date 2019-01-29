#pragma once

class VertexBuffer
{
private:
	unsigned int m_RendererID; //ID for basically every object we make (shader, buffer, texture...) / numeric ID btw
	//keeps track of every type of object created
public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;
};