#pragma once
#include "VertexBuffer.h"

// Forward declaration to avoid recursive includings
class VertexBufferLayout;

class VertexArray 
{
private:
	unsigned int m_RendererID;
public:
	VertexArray();
	~VertexArray();

	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& vbl);

	void Bind() const;
	void Unbind() const;
};