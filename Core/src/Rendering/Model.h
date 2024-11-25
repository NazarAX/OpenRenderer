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

struct Transform
{
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale = glm::vec3(1.0f); // Default scale to 1.0

    static glm::mat4 GetModelMatrix(Transform&, std::shared_ptr<Camera>);
};

struct Mesh
{
    VertexArray vertexArray;
    IndexBuffer indexBuffer;
    Material material;
    std::string name;
    Transform transform;
};

class Model
{
private:
    std::vector<Mesh> meshes;
    Transform transform;
    std::string name;
public:
    Model() = default;
    ~Model() = default;

    void LoadFromFile(const std::string& fileName);


    void SetTransform(const Transform& _transform) {transform = _transform;}
    Transform GetTransform() const { return transform; }
    std::string GetName() const { return name; }
    const std::vector<Mesh>& GetMeshes() const { return meshes; }
};


#endif //MODEL_H
