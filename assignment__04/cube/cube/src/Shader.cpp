#include "Shader.h"
#include <GL/glew.h>
#include<iostream>
#include<string>
#include<fstream>

Shader::Shader(const string& vsFilePath, const string& fsFilePath)
	:ID(0)
{
	shaderCode.vetexShader = readShader(vsFilePath);

	shaderCode.fragmentShader = readShader(fsFilePath);

	GLC(ID = createShader(shaderCode.vetexShader, shaderCode.fragmentShader));

}

Shader::~Shader()
{
	GLC(glDeleteProgram(ID));
}
unsigned int Shader::compileShader(unsigned int type, const string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);


	// Error 
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		cout << "Failed to compile " << ((type == GL_VERTEX_SHADER) ? "vertex" : "fragment") << endl;
		cout << message << endl;
		glDeleteShader(id);

		return 0;
	}

	return id;
}

unsigned int Shader::createShader(const string& vertexShader, const string& fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;


}
void Shader::bind() const
{
	GLC(glUseProgram(ID));
}
void Shader::unbind() const
{
	GLC(glUseProgram(0));
}
void Shader::setUniform4f(const string& name, float v0, float v1, float v2, float v3)
{
	GLC(glUniform4f(getUniformLocation(name), v0, v1, v2, v3));
}

void Shader::setUniform1i(const string& name, int value)
{
	GLC(glUniform1i(getUniformLocation(name), value));
}

void Shader::setUniformMat4f(const string& name, const glm::mat4& mat)
{
	glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &mat[0][0]);
}

int Shader::getUniformLocation(const string& name) {
	GLC(int location = glGetUniformLocation(ID, name.c_str()));
	if (location == -1) {
		cout << "Uniform " << name << " doesn't exist" << endl;
	}
	return location;
}

string Shader::readShader(string filePath)
{
	ifstream t(filePath);
	string str((istreambuf_iterator<char>(t)), istreambuf_iterator<char>());

	return str;
}