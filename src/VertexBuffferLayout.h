#pragma once

#include <vector>

#include "Renderer.h"

struct VertexButterElement
{
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int GetSizeofType(const unsigned int type) {
		switch (type)
		{
			case GL_FLOAT:			return 4;
			case GL_UNSIGNED_INT:	return 4;
			case GL_UNSIGNED_BYTE:	return 1;
		}

		ASSERT(false);
		return 0;
	}
};

class VertexArrayLayout {
public:
	VertexArrayLayout() 
		:m_stride(0) {}

	// 模板
	template <typename T>
	void Push(unsigned int count) {
		static_assert(false);
	}

	// 模板的特化
	template<>
	void Push<float>(unsigned int count) {
		m_elements.push_back({ GL_FLOAT, count, GL_FALSE });
		m_stride += count * VertexButterElement::GetSizeofType(GL_FLOAT);
	}

	template<>
	void Push<unsigned int>(unsigned int count) {
		m_elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		m_stride += count * VertexButterElement::GetSizeofType(GL_UNSIGNED_INT);
	}

	template<>
	void Push<unsigned char>(unsigned int count) {
		m_elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		m_stride += count * VertexButterElement::GetSizeofType(GL_UNSIGNED_BYTE);
	}

	inline const std::vector<VertexButterElement> GetElements() const { return m_elements; }
	inline unsigned int GetStride() const { return m_stride; }

private:
	std::vector<VertexButterElement> m_elements;
	unsigned int m_stride;
};