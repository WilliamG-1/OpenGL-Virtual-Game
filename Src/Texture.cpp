#include "Texture.h"
#include <iostream>

Texture::Texture(const std::string& texFilePath)
	:
	filePath(texFilePath), 
	texID(0),
	width(0), height(0), nrChannels(0),
	data(nullptr)
{
	
	glGenTextures(1, &texID);
	stbi_set_flip_vertically_on_load(1);
	std::cout << filePath << std::endl;
}

void Texture::init()
{
	std::cout << "Loading from: " << filePath << std::endl;
	data = stbi_load(filePath.c_str(), &width, &height, &nrChannels, 4);
	glBindTexture(GL_TEXTURE_2D, texID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	// Free data after buffering it lmao
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(data);
	}
	else {
		std::cout << "Error,  unable to load Texture! No data found!" << std::endl;
	}
	
}

void Texture::setVertAttribs(unsigned int layoutLocation, int count, unsigned int stride, unsigned int offset)
{
	bind();
	glVertexAttribPointer(layoutLocation, count, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(offset * sizeof(float)));
	glEnableVertexAttribArray(layoutLocation);
}

void Texture::bind(unsigned int textureSlot)
{
	glActiveTexture(GL_TEXTURE0 + textureSlot);
	glBindTexture(GL_TEXTURE_2D, texID);
}

void Texture::unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture()
{
	glDeleteTextures(1, &texID);
}