#define STB_IMAGE_IMPLEMENTATION
#include "Texture.h"

Texture::Texture()
{
	textureID = 0;
	width = 0;
	heigth = 0;
	bitDepth = 0;
	fileLocation = "";
}

Texture::Texture(std::string fileLoc)
{
	textureID = 0;
	width = 0;
	heigth = 0;
	bitDepth = 0;
	fileLocation = fileLoc;
}

void Texture::LoadTexture()
{
	unsigned char* textData = stbi_load(fileLocation.c_str(), &width, &heigth, &bitDepth, 0);
	if (!textData)
	{
		printf("Failed to find: %s\n", fileLocation);
		return;
	}
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D,textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,heigth,0,GL_RGBA,GL_UNSIGNED_BYTE,textData);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	stbi_image_free(textData);
}

void Texture::UseTexture()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D,textureID);
}

void Texture::ClearTexture()
{
	glDeleteTextures(1, &textureID);
	textureID = 0;
	width = 0;
	heigth = 0;
	bitDepth = 0;
	fileLocation = "";

}

Texture::~Texture()
{
	ClearTexture();
}