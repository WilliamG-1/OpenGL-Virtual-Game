#pragma once
#include "VertexBuffer.h"
#include "ElementBuffer.h"
#include <vector>

struct Arrays {
	float vertices[40];
	unsigned int indices[12];

};

class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void init(struct Arrays A, int VBO_Array_Size, int EBO_Array_Size);
	void init(float* vertices, int VBO_Array_Size, unsigned int* indices, int EBO_Array_Size);
	void bind();
	void bindBuffers(struct Arrays A, int VBO_Array_Size, int EBO_Array_Size);
	void bindVBO(unsigned int index);
	void setVertexAttribPointersf(int layoutLocation, int sizeData, int stride, int offset);
	void bufferVertexData(int arraySize, float* data);
	int getElementCount(int EBOIndex) const;
private:
	unsigned int vertexArrayObject;
	VertexBuffer vbo;
	ElementBuffer ebo;
	std::vector<VertexBuffer> VBO_Container;
	std::vector<ElementBuffer> EBO_Container;

	unsigned int VBO_Count;
	unsigned int EBO_Count;
};

