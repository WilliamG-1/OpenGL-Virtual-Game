#include "ElementBuffer.h"
#include <glad/glad.h>

ElementBuffer::ElementBuffer()
	:
	elementBufferObject(0), elementCount(0)
{
	
}

void ElementBuffer::init(unsigned int data[], int count)
{
	glGenBuffers(1, &elementBufferObject);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);

	elementCount = count;
}

unsigned int ElementBuffer::getBufferID() const
{
	return elementBufferObject;
}

unsigned int ElementBuffer::getElementCount() const
{ 
	return elementCount;
}

ElementBuffer::~ElementBuffer()
{
	glDeleteBuffers(1, &elementBufferObject);
}