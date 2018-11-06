#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
	// give ID to our buffer
	GLC(glGenBuffers(1, &ID));
	//select that buffer
	GLC(glBindBuffer(GL_ARRAY_BUFFER, ID));
	//add data to my buffer
	GLC(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
	GLC(glDeleteBuffers(1, &ID));
}

void VertexBuffer::bind() const
{
	GLC(glBindBuffer(GL_ARRAY_BUFFER, ID));
}
void VertexBuffer::unbind() const
{ 
	GLC(glBindBuffer(GL_ARRAY_BUFFER, 0));
}