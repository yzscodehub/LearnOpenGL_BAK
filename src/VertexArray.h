#pragma once

#include "VertexBuffer.h"
#include "VertexBuffferLayout.h"

class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void AddBuffer(const VertexBuffer& vb, const VertexArrayLayout& layout);

private:

};

