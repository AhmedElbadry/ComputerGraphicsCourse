#pragma once
#include <string>
#include "global.h"


using namespace std;

class Texture
{
public:
	Texture(const string& path);
	~Texture();

	void bind(unsigned int slot = 0) const;
	void unbind() const;

	inline int getWidth() const { return width; }
	inline int getHeight() const { return height; }
private:
	unsigned int ID;
	string filePath;
	unsigned char* localBuffer;
	int width, height, bitsPerPixel;

};

