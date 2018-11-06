#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

uniform mat4 m_mvp;

out vec2 v_texCoord;

void main()
{
	gl_Position = m_mvp*position;

	v_texCoord = texCoord;
}