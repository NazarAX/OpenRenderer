//
// Created by Nazarii on 11/20/2024.
//

#ifndef MODEL_H
#define MODEL_H
#include "Interface/Buffers.h"
#include "Interface/Abstractions.h"
#include "Camera.h"
#include <vector>

#include "Material.h"


struct Mesh
{
    VertexArray vertexArray;
    IndexBuffer indexBuffer;
    Material material;
    std::string name;
};

class Model {
private:
    std::vector<Mesh> meshes;
    std::string name;
public:
    Model() = default;
    Model(const std::string& fileName) {
        LoadFromFile(fileName);
    }
    ~Model() = default;

    void LoadFromFile(const std::string& fileName);

    std::string GetName() const { return name; }
    const std::vector<Mesh>& GetMeshes() const { return meshes; }
};


#endif //MODEL_H
