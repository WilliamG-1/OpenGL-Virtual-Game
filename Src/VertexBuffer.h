#pragma once
class VertexBuffer
{
public:
	VertexBuffer();
	~VertexBuffer();

	void init(float vertexData[], int count);
	void bufferData(int sizeOfArray, float vertexData[]);
	void bind();
	unsigned int getVertexID() const;
private:
	unsigned int vertexBufferObject;

	int size;

};

