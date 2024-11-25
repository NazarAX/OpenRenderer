//
// Created by Nazarii on 11/20/2024.
//

#include "Model.h"
#include <iostream>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "glad/glad.h"

#define ASSIMP_LOAD_FLAGS (aiProcess_Triangulate | aiProcess_GenNormals | aiProcess_JoinIdenticalVertices | aiProcess_FixInfacingNormals)


static VertexData ParseMesh(aiMesh* mesh, const aiScene* scene) {

    VertexData vertexData;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        // Position
        aiVector3D position = mesh->mVertices[i];
        aiVector3D normal = mesh->mNormals[i];
        aiVector3D uv = mesh->HasTextureCoords(0)? mesh->mTextureCoords[0][i] : aiVector3D{0.0f, 0.0f , 0.0f};

        vertexData.Positions.push_back({ position.x, position.y, position.z });
        vertexData.Normals.push_back({ normal.x, normal.y, normal.z });
        vertexData.TexCoords.push_back({ uv.x, uv.y });
    }

    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];

        vertexData.Indices.push_back(face.mIndices[0]);
        vertexData.Indices.push_back(face.mIndices[1]);
        vertexData.Indices.push_back(face.mIndices[2]);

    }

    return vertexData;
}

static Mesh GenerateMesh(VertexData& data, Material material, Transform transform, const std::string& name)
{
    VertexArray vertexArray;
    VertexBuffer positionBuffer = VertexBuffer(data.Positions.data(), data.Positions.size()* sizeof(glm::vec3));
    VertexBuffer normalsBuffer = VertexBuffer(data.Normals.data(), data.Normals.size()* sizeof(glm::vec3));
    VertexBuffer uvBuffer = VertexBuffer(data.TexCoords.data(), data.TexCoords.size()* sizeof(glm::vec3));

    IndexBuffer indexBuffer(data.Indices.data(), data.Indices.size());

    vertexArray.Bind();
    vertexArray.AddBuffer(positionBuffer, Coordinates, 3);
    vertexArray.AddBuffer(normalsBuffer, NormalCoords, 3);
    vertexArray.AddBuffer(uvBuffer, TexCoords, 2);

    return Mesh{vertexArray, indexBuffer, material, name, transform};
}


static void ProcessNode(aiNode* node, const aiScene* scene, std::vector<Mesh>& meshes)
{

    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        VertexData vertexData = ParseMesh(mesh, scene);

        meshes.push_back(GenerateMesh(vertexData, Material{}, Transform{}, mesh->mName.C_Str()));
    }

    //children nodes
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        ProcessNode(node->mChildren[i], scene, meshes);
    }
}



void Model::LoadFromFile(const std::string& fileName)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(fileName,
        aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cerr << "Assimp Error: " << importer.GetErrorString() << std::endl;
        return;
    }

    // Recursively process each node in the scene
    ProcessNode(scene->mRootNode, scene, meshes);
}



