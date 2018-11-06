#include <GL/glew.h>
#include<iostream>
using namespace std;
void GLClearError() {
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line) {
	while (GLenum error = glGetError())
	{
		cout << "OpenGL error: " << error << "   ";
		cout << "function: " << function << "   ";
		cout << "file: " << file << "   ";
		cout << "line: " << line << endl;
		return false;
	}
	return true;
}