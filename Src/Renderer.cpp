#include "Renderer.h"

Renderer::Renderer()
{

}

void Renderer::draw(VertexArray& VAO, Shader& shader)
{
	VAO.bind();
	shader.use();	
    glDrawElements(GL_TRIANGLES, VAO.getElementCount(0), GL_UNSIGNED_INT, nullptr);
}

Renderer::~Renderer()
{

}
