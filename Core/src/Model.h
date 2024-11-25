//
// Created by Nazarii on 11/20/2024.
//

#ifndef MODEL_H
#define MODEL_H
#include "Rendering/Buffers.h"
#include "Rendering/Abstractions.h"
#include <vector>


struct Mesh {
    VertexArray vertexArray;
    IndexBuffer indexBuffer;
    std::string name;
};

class Model {
private:
    std::vector<Mesh> meshes;

public:
    Model() = default;
    ~Model() = default;

    void LoadFromFile(const std::string& fileName);

    const std::vector<Mesh>& GetMeshes() const { return meshes; }
};


#endif //MODEL_H
