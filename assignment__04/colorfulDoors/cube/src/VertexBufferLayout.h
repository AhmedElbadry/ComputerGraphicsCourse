#pragma once

#include <vector>
#include <GL/glew.h>
#include "global.h"
using namespace std;

struct VBL_Element
{
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int getSizeOfType(unsigned int type)
	{
		switch (type)
		{
			case GL_FLOAT: return 4;
			case GL_UNSIGNED_INT: return 4;
			case GL_UNSIGNED_BYTE: return 1;

		}
		ASSERT(false);
		return 0;

	}
};

class VertexBufferLayout
{
public:
	VertexBufferLayout()
		:stride(0){}


	template <typename T>
	void push(unsigned int count)
	{
		static_assert(false);
	}

	template <>
	void push<float>(unsigned int count)
	{
		VBL_Elements.push_back({GL_FLOAT, count, GL_FALSE});
		stride += count * VBL_Element::getSizeOfType(GL_FLOAT);
	}

	template <>
	void push<unsigned int>(unsigned int count)
	{
		VBL_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		stride += count * VBL_Element::getSizeOfType(GL_UNSIGNED_INT);
	}


	template <>
	void push<unsigned char>(unsigned int count)
	{
		VBL_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		stride += count * VBL_Element::getSizeOfType(GL_UNSIGNED_BYTE);
	}

	inline const vector<VBL_Element> getElements() const { return VBL_Elements; }
	inline unsigned int getStride() const { return stride; }

private:
	vector <VBL_Element> VBL_Elements;
	unsigned int stride;

};

