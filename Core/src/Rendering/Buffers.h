#pragma once
#include <memory>
#include <string>
#include <glm/glm.hpp>
#include <vector>


/*
    layout of vertex array
*/
struct VertexLayout
{
    unsigned int coords = 0;
    unsigned int colors = 0;
    unsigned int texCoords = 0;
    unsigned int normalCoords = 0;
};

/*
    Minimalistic vertex buffer abstraction
*/


class VertexBuffer
{
private:
    VertexLayout layout;
    unsigned int id;
public:
    VertexBuffer();
    VertexBuffer(float* data, unsigned int size, VertexLayout layout);
    ~VertexBuffer();

    void SetData(float* data, unsigned int size, VertexLayout layout);

    void Bind() const;
    void Unbind() const;
public:
    inline VertexLayout GetLayout() const { return layout; }
    inline unsigned int GetId() const { return id; }
};

/*
    Minimalistic vertex array abstraction
*/


class VertexArray
{
private:
    unsigned int id;
    std::vector<std::shared_ptr<VertexBuffer>> buffers; // Consistent use of shared_ptr

public:
    VertexArray();
    VertexArray(std::shared_ptr<VertexBuffer> buffer);
    VertexArray(float* data, unsigned int size, VertexLayout layout);
    ~VertexArray();

    void AddVertexBuffer(std::shared_ptr<VertexBuffer> buffer);
    void AddVertexBuffer(float* data, unsigned int size, VertexLayout layout);

public:
    void Bind() const;
    void Unbind() const;

    unsigned int GetId() const { return id; }
    std::shared_ptr<VertexBuffer> GetVertexBuffer(unsigned int index) const;
};



// class VertexArray
// {
// private:
// 	unsigned int id;
// 	unsigned int vbo;
// 	VertexLayout layout;

// public:
// 	VertexArray() {}
// 	VertexArray(VertexLayout layout, float* data, unsigned int size);
// 	~VertexArray() {} 

// public:
// 	void Bind();
// 	void Unbind();

// 	unsigned int GetId() { return id; }
// 	unsigned int GetVBO() { return vbo; }
// };

/*
    Minimalistic index buffer abstraction
*/





