#pragma once
#include "VertexBuffer.h"
#include "ElementBuffer.h"
#include <vector>

struct Arrays {
	float vertices[20];
	unsigned int indices[6];
};

class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void init(struct Arrays A, int VBO_Array_Size, int EBO_Array_Size);
	void bind();
	void bindBuffers(struct Arrays A, int VBO_Array_Size, int EBO_Array_Size);
	void setVertexAttribPointersf(int layoutLocation, int sizeData, int stride, int offset);

	int getElementCount(int EBOIndex) const;
private:
	unsigned int vertexArrayObject;
	std::vector<VertexBuffer> VBO_Container;
	std::vector<ElementBuffer> EBO_Container;

	static unsigned int VBO_Count;
	static unsigned int EBO_Count;
};

