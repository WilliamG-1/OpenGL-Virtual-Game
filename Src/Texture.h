#pragma once
#include <string>
#include <glad/glad.h>
#include <stb_image/stb_image.h>

class Texture
{
public:
	Texture(const std::string& texFilePath);
	~Texture();

	void init();
	void setVertAttribs(unsigned int layoutLocation, int count, unsigned int stride, unsigned int offset);
	void bind(unsigned int textureSlot = 0);
	void unbind();
private:
	unsigned int texID;
	int width, height, nrChannels;
	std::string filePath;
	unsigned char* data;
};

