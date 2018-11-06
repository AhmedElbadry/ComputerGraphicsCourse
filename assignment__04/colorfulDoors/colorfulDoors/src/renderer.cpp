#include <GL/glew.h>
#include<iostream>

#include "renderer.h"
using namespace std;


void Renderer::draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
	shader.bind();
	va.bind();
	ib.bind();
	GLC(glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr));
}

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}