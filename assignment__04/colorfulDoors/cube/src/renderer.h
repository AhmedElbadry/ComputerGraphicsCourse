#pragma once
#include <GL/glew.h>
#include "global.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"






class Renderer
{
public:
	Renderer();
	~Renderer();

	void draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader ) const;

private:

};

