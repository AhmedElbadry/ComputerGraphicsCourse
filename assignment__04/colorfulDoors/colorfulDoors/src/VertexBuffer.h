#pragma once
#include "global.h"

class VertexBuffer
{
public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();
	void bind() const;
	void unbind() const;

private:

	unsigned int ID;

};

