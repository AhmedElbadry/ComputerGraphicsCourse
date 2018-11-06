#pragma once
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "global.h"
class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

	void bind() const;
	void unbind() const;

private:
	unsigned int ID;

};
