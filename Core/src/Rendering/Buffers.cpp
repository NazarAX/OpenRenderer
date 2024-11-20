#include "Buffers.h"
#include <glad/glad.h>
#include "../Utils.h"
#include <glm/gtc/type_ptr.hpp>
#include <sstream>
#include <iostream>

/*
    Vertex buffer implementation
*/

VertexBuffer::VertexBuffer()
    : id(0), layout({})
{
    glGenBuffers(1, &id);
}

VertexBuffer::VertexBuffer(float* data, unsigned int size, VertexLayout layout)
    : layout(layout)
{
    glGenBuffers(1, &id);
    Bind();
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer() {
    if (id) {
        std::cout << "Deleting VertexBuffer: " << id << std::endl;
        glDeleteBuffers(1, &id);
    }
}

void VertexBuffer::SetData(float* data, unsigned int size, VertexLayout layout)
{
    this->layout = layout;
    Bind();
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void VertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, id);
}

void VertexBuffer::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}


/*
    Vertex array implementation
*/
VertexArray::VertexArray()
    : id(0)
{
    glGenVertexArrays(1, &id);
}

VertexArray::VertexArray(std::shared_ptr<VertexBuffer> buffer)
    : id(0)
{
    glGenVertexArrays(1, &id);
    AddVertexBuffer(buffer);
}

VertexArray::VertexArray(float* data, unsigned int size, VertexLayout layout)
    : id(0)
{
    glGenVertexArrays(1, &id);
    auto buffer = std::make_shared<VertexBuffer>(data, size, layout);
    AddVertexBuffer(buffer);
}

void VertexArray::AddVertexBuffer(float* data, unsigned int size, VertexLayout layout)
{
    glGenVertexArrays(1, &id);
    auto buffer = std::make_shared<VertexBuffer>(data, size, layout);
    AddVertexBuffer(buffer);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &id);
}

void VertexArray::AddVertexBuffer(std::shared_ptr<VertexBuffer> buffer)
{
    Bind();
    buffer->Bind();

    VertexLayout layout = buffer->GetLayout();
    unsigned int offset = 0;
    
    unsigned int stride = sizeof(float) * (layout.colors + layout.coords + layout.normalCoords + layout.texCoords);

    glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, layout.coords, GL_FLOAT, GL_FALSE, stride, 0);

	if (layout.colors)
	{
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, layout.colors, GL_FLOAT, GL_FALSE, stride, (void*) (sizeof(float) * layout.coords));
	}

	if (layout.texCoords)
	{
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, layout.texCoords, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * (layout.coords + layout.colors)));
	}

	if (layout.normalCoords)
	{
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, layout.normalCoords, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * (layout.coords + layout.colors + layout.texCoords)));
	}

    buffers.push_back(buffer);
}

void VertexArray::Bind() const
{
    glBindVertexArray(id);
}

void VertexArray::Unbind() const
{
    glBindVertexArray(0);
}

std::shared_ptr<VertexBuffer> VertexArray::GetVertexBuffer(unsigned int index) const
{
    if (index >= buffers.size())
        throw std::out_of_range("VertexBuffer index out of range");
    return buffers[index];
}





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