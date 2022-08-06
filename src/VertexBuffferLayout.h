#pragma once

#include <vector>

#include "GL/glew.h"

struct VertexButterElement
{
	unsigned int type;
	unsigned int count;
	bool normalized;
};

class VertexArrayLayout {
public:
	VertexArrayLayout() 
		:m_stride(0) {}

	template <typename T>
	void Push(unsigned int count) {
		static_assert(false);
	}

	template<>
	void Push<float>(unsigned int count) {
		m_elements.push_back({ GL_FLOAT, count, false });
		m_stride += sizeof(GL_FLOAT);
	}

	template<>
	void Push<unsigned int>(unsigned int count) {
		m_elements.push_back({ GL_UNSIGNED_INT, count, false });
		m_stride += sizeof(GLuint);
	}

	template<>
	void Push<unsigned char>(unsigned int count) {
		m_elements.push_back({ GL_UNSIGNED_BYTE, count, false });
		m_stride += sizeof(GLbyte);
	}

	inline const std::vector<VertexButterElement> GetElements() const { return m_elements; }
	inline unsigned int GetStride() const { return m_stride; }

private:
	std::vector<VertexButterElement> m_elements;
	unsigned int m_stride;
};