#pragma once


class IndexBuffer
{
public:
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();

	void Bind() const;
	void UnBind() const;

	inline unsigned int GetCount() { return m_count; }

private:
	unsigned int m_rendererID;
	unsigned int m_count;
};

