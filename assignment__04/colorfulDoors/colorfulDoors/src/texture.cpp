#include <string>
#include <iostream>
#include "texture.h"
#include "global.h"
#include <stb_image/stb_image.h>

using namespace std;

Texture::Texture(const string& path)
	:ID(0), filePath(path), localBuffer(nullptr), width(0), height(0), bitsPerPixel(0)
{
	stbi_set_flip_vertically_on_load(true);
	localBuffer = stbi_load(filePath.c_str(), &width, &height, &bitsPerPixel, 4);

	
    

	GLC(glGenTextures(1, &ID));
	GLC(glBindTexture(GL_TEXTURE_2D, ID));
	
	// set texture filtering parameters
	GLC(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLC(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

	// set the texture wrapping parameters
	GLC(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
	GLC(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));



	if (localBuffer)
	{
		GLC(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer));
		GLC(glGenerateMipmap(GL_TEXTURE_2D));
	}
	else
	{
		cout << "Failed to load texture" << endl;
		cout << "the file path " << filePath << endl;
	}
	stbi_image_free(localBuffer);

	GLC(glBindTexture(GL_TEXTURE_2D, 0));
}

Texture::~Texture()
{
	GLC(glDeleteTextures(1, &ID));
}


void Texture::bind(unsigned int slot) const
{
	GLC(glActiveTexture(GL_TEXTURE0 + slot));
	GLC(glBindTexture(GL_TEXTURE_2D, ID));
}
void Texture::unbind() const
{
	GLC(glBindTexture(GL_TEXTURE_2D, 0));
}