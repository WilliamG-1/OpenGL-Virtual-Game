#include "VertexArray.h"
#include <glad/glad.h>

// Specify
// 1.) VBO Array
// 2.) VBO vertices count
// 3.) EBO Array
// 4.) EBO indices count

VertexArray::VertexArray()
{
	
}

void VertexArray::init(struct Arrays A, int VBO_Array_Size, int EBO_Array_Size)
{
	
	glGenVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);
	// Create a VBO and EBO and put them into our container
	VertexBuffer VBO;
	ElementBuffer EBO;

	VBO_Container.push_back(VBO);
	EBO_Container.push_back(EBO);

	VBO_Container[0].init(A.vertices, VBO_Array_Size);
	EBO_Container[0].init(A.indices, EBO_Array_Size);
	
	VBO_Count++;
	EBO_Count++;
}

void VertexArray::init(float* vertices, int VBO_Array_Size, unsigned int* indices, int EBO_Array_Size)
{

	glGenVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);

	vbo.init(vertices, VBO_Array_Size);
	ebo.init(indices, EBO_Array_Size);
	this->VBO_Count++;
	this->EBO_Count++;
}

void VertexArray::bindBuffers(struct Arrays A, int VBO_Array_Size, int EBO_Array_Size)
{
	// Bind this-> VAO, so future bounds belong to this vao
}

void VertexArray::bindVBO(unsigned int index)
{
	vbo.bind();
}

void VertexArray::setVertexAttribPointersf(int layoutLocation, int sizeData, int stride, int offset)
{
	glVertexAttribPointer(layoutLocation, sizeData, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)offset);
	glEnableVertexAttribArray(layoutLocation);
}


void VertexArray::bufferVertexData(int arraySize, float* data)
{
	bind();
	vbo.bufferData(arraySize, data);
}

void VertexArray::bind()
{
	glBindVertexArray(this->vertexArrayObject);
}

int VertexArray::getElementCount(int EBOIndex) const
{
	return ebo.getElementCount();
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &vertexArrayObject);
}