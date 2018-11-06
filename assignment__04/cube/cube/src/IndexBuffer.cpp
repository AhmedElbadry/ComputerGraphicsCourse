#include "IndexBuffer.h"
#include "global.h"
IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
	:m_Count(count)
{
	// give ID to our buffer
	GLC(glGenBuffers(1, &ID));
	//select that buffer
	GLC(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID));
	//add data to my buffer
	GLC(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count*sizeof(GLuint), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer()
{
	GLC(glDeleteBuffers(1, &ID));
}

void IndexBuffer::bind() const
{
	GLC(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID));
}
void IndexBuffer::unbind() const
{
	GLC(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}