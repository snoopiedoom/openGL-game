#pragma once

//The whole point of an index buffer is that it allows us to re-use our verdices

class IndexBuffer
{
private:
	unsigned int m_RendererID; //ID for basically every object we make (shader, buffer, texture...) / numeric ID btw
	unsigned int m_Count; //number of indeces
public:
	IndexBuffer(const unsigned int* data, unsigned int count); //size - in bytes, count - element count
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	inline unsigned int GetCount() const { return m_Count; }
};