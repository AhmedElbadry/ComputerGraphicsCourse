#pragma once
#include "vertexArray.h"
#include "VertexBufferLayout.h"


VertexArray::VertexArray()
{
	GLC(glGenVertexArrays(1, &ID));
	//GLC(glBindVertexArray(ID));
}
VertexArray::~VertexArray()
{
	GLC(glDeleteVertexArrays(1, &ID));
}

void VertexArray::addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	//bind vertex array
	bind();
	//bind vertex buffer
	vb.bind();


	//setup layout
	const auto& elements = layout.getElements();

	unsigned int offset = 0;

	for (unsigned int i = 0; i < elements.size(); i++)
	{


		GLC(glEnableVertexAttribArray(i));

		GLC(glVertexAttribPointer(i, elements[i].count, elements[i].type,
			elements[i].normalized, layout.getStride(), (const void*)offset));
		offset += elements[i].count*VBL_Element::getSizeOfType(elements[i].type);

	}

	
}
void VertexArray::bind() const 
{
	GLC(glBindVertexArray(ID));
}
void VertexArray::unbind() const
{
	GLC(glBindVertexArray(0));
}
