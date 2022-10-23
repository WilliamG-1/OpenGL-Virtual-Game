#include "VertexBuffer.h"
#include <glad/glad.h>
VertexBuffer::VertexBuffer()
	:
	vertexBufferObject(0), size(0)
{
	
}

void VertexBuffer::init(float vertexData[], int count)
{
	glGenBuffers(1, &vertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(float), vertexData, GL_STATIC_DRAW);
}

void VertexBuffer::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, this->vertexBufferObject);
}

void VertexBuffer::bufferData(int arraySize, float data[])
{
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, arraySize * sizeof(float), data, GL_STATIC_DRAW);
}
unsigned int VertexBuffer::getVertexID() const
{
	return vertexBufferObject;
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &vertexBufferObject);
}