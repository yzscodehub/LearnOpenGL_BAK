#pragma once

#include "VertexBuffer.h"
#include "VertexBuffferLayout.h"

class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void Bind() const;
	void UnBind() const;

	void AddBuffer(const VertexBuffer& vb, const VertexArrayLayout& layout);

private:
	unsigned int m_rendererID;
};

