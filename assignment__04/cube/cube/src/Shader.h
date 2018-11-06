#pragma once
#include <string>
#include "global.h"
#include <glm/glm.hpp>
using namespace std;


struct ShaderCode
{
	string vetexShader;
	string fragmentShader;
};

class Shader
{
public:
	Shader(const string& vsFilePath, const string& fsFilePath);
	~Shader();

	void bind() const;
	void unbind() const;

	void setUniform4f(const string& name, float v0, float v1, float v2, float v3);
	void setUniform1i(const string& name, int value);
	void setUniformMat4f(const string& name, const glm::mat4& mat);
private:
	ShaderCode shaderCode;
	unsigned int ID;
	int getUniformLocation(const string& name);


	unsigned int compileShader(unsigned int type, const string& source);
	unsigned int createShader(const string& vertexShader, const string& fragmentShader);

	string readShader(string filePath);

};
