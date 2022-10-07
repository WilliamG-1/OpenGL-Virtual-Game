#include "VertexArray.h"
#include <glad/glad.h>
unsigned int VertexArray::VBO_Count;
unsigned int VertexArray::EBO_Count;
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


	
	VertexArray::VBO_Count++;
	VertexArray::EBO_Count++;
}

void VertexArray::init(float* vertices, int VBO_Array_Size, unsigned int* indices, int EBO_Array_Size)
{
	glGenVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);

	VertexBuffer VBO;
	ElementBuffer EBO;
	
	VBO_Container.push_back(VBO);
	EBO_Container.push_back(EBO);

	VBO_Container[0].init(vertices, VBO_Array_Size);
	EBO_Container[0].init(indices, EBO_Array_Size);
}

void VertexArray::bindBuffers(struct Arrays A, int VBO_Array_Size, int EBO_Array_Size)
{
	// Bind this-> VAO, so future bounds belong to this vao
	glBindVertexArray(vertexArrayObject);
	// Declare Buffers
	VertexBuffer VBO;
	ElementBuffer EBO;
	

	VBO_Container.push_back(VBO);
	EBO_Container.push_back(EBO);

	VBO_Container[VertexArray::VBO_Count].init(A.vertices, VBO_Array_Size);
	EBO_Container[VertexArray::EBO_Count].init(A.indices, EBO_Array_Size);

	// Increase count of VBO and EBO
	VertexArray::VBO_Count++;
	VertexArray::EBO_Count++;
}

void VertexArray::setVertexAttribPointersf(int layoutLocation, int sizeData, int stride, int offset)
{
	glVertexAttribPointer(layoutLocation, sizeData, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)offset);
	glEnableVertexAttribArray(layoutLocation);
}

void VertexArray::bind()
{
	glBindVertexArray(vertexArrayObject);

}

int VertexArray::getElementCount(int EBOIndex) const
{
	return EBO_Container[EBOIndex].getElementCount();
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &vertexArrayObject);
}