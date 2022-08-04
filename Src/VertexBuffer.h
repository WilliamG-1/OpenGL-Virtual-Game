#pragma once
class VertexBuffer
{
public:
	VertexBuffer();
	~VertexBuffer();

	void init(float vertexData[], int count);

	unsigned int getVertexID() const;
private:
	unsigned int vertexBufferObject;

	int size;

};

