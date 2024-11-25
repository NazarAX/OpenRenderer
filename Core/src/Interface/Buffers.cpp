#include "Buffers.h"
#include <glad/glad.h>
#include "../Utils.h"
#include <glm/gtc/type_ptr.hpp>
#include <sstream>
#include <iostream>



#define DEBUG
/*
 *	Vertex Buffer implementation
 *
 */

VertexBuffer::VertexBuffer(const void* data, unsigned int size) {
	glGenBuffers(1, &m_RendererID);
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

#ifdef DEBUG
	std::cout << "Creating buffer :" << m_RendererID << std::endl;
#endif
}

VertexBuffer::~VertexBuffer() {
	//glDeleteBuffers(1, &m_RendererID);

#ifdef DEBUG
	std::cout << "~VertexBuffer :" << m_RendererID << std::endl;
#endif
}

void VertexBuffer::Bind() const {
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
#ifdef DEBUG
	std::cout << "Binding buffer :" << m_RendererID << std::endl;
#endif

}

void VertexBuffer::Unbind() const {
	glBindBuffer(GL_ARRAY_BUFFER, 0);

#ifdef DEBUG
	std::cout << "Unbinding buffer :" << m_RendererID << std::endl;
#endif

}

/*
 *	Vertex Array implementation
 *
 */


VertexArray::VertexArray() {
	glGenVertexArrays(1, &m_RendererID);

#ifdef DEBUG
	std::cout << "Creating array :" << m_RendererID << std::endl;
#endif
}

VertexArray::~VertexArray() {
	//glDeleteVertexArrays(1, &m_RendererID);
#ifdef DEBUG
	std::cout << "Deleting array :" << m_RendererID << std::endl;
#endif
}

void VertexArray::Bind() const {
	glBindVertexArray(m_RendererID);
#ifdef DEBUGX
	std::cout << "Binding array :" << m_RendererID << std::endl;
#endif

}

void VertexArray::Unbind() const {
	glBindVertexArray(0);

#ifdef DEBUG
	std::cout << "Unbinding array :" << m_RendererID << std::endl;
#endif


}

void VertexArray::AddBuffer(const VertexBuffer &buffer, BufferIndex bindMode, unsigned int size) {
	Bind();
	buffer.Bind();
	glEnableVertexAttribArray(bindMode);
	glVertexAttribPointer(bindMode, size, GL_FLOAT, GL_FALSE, sizeof(float) * size, 0);

#ifdef DEBUG
	std::cout << "Adding attrib : " << bindMode << " to array :" << m_RendererID << std::endl;
#endif
}

void VertexArray::AddBuffer(const std::vector<float> &data, BufferIndex bindMode, unsigned int size)
{
	Bind();
	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, size, data.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(bindMode);
	glVertexAttribPointer(bindMode, size, GL_FLOAT, GL_FALSE, sizeof(float) * size, 0);
}


/*
 *
 *  IndexBuffer implementation
 *
 */

IndexBuffer::IndexBuffer(unsigned int* data, int count) : count(count)
{
	glGenBuffers(1, &id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

void IndexBuffer::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}


void IndexBuffer::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}