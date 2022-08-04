#pragma once
class ElementBuffer
{
public:
	ElementBuffer();
	~ElementBuffer();

	void init(unsigned int data[], int count);

	unsigned int getBufferID() const;
	unsigned int getElementCount() const;

private:
	unsigned int elementBufferObject;
	unsigned int elementCount;
};

