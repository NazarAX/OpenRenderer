#pragma once
#include <memory>
#include <string>
#include <glm/glm.hpp>
#include <vector>



// struct VertexArrayLayout
// {
//     unsigned int coords = 0;
//     unsigned int colors = 0;
//     unsigned int texCoords = 0;
//     unsigned int normalCoords = 0;
// };

enum BufferIndex
{
    Coordinates = 0,
    Colors = 1,
    TexCoords = 2,
    NormalCoords = 3,
    AOS = -1
};


struct VertexData
{
	std::vector<glm::vec3> Positions;
	std::vector<glm::vec2> TexCoords;
	std::vector<glm::vec3> Normals;
	std::vector<unsigned int> Indices;
};

class VertexBuffer {
private:
	unsigned int m_RendererID;
public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;

	unsigned int GetRendererID() const { return m_RendererID; }
};


class VertexArray {
private:
	unsigned int m_RendererID;
public:
	VertexArray();
	~VertexArray();

	void Bind() const;
	void Unbind() const;

	void AddBuffer(const VertexBuffer& buffer, BufferIndex bindMode, unsigned int size);
	void AddBuffer(const std::vector<float>& data, BufferIndex bindMode, unsigned int size);


	unsigned int GetRendererID() const { return m_RendererID; }
};


/*
    Index buffer abstraction
*/

class IndexBuffer
{
private:
	unsigned int id;
	int count;
public:
	IndexBuffer() {}
	IndexBuffer(unsigned int* indices, int count);
	~IndexBuffer() {}

public:
	void Bind();
	void Unbind();
	unsigned int GetId() const { return id; }
	float GetCount() const { return count; };

};



