#pragma once
#include "global.h"

class IndexBuffer
{
public:
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();
	void bind() const;
	void unbind() const;

	inline int getCount() const { return m_Count; }

private:

	unsigned int ID;
	unsigned int m_Count;



};

