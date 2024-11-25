//
// Created by Nazarii on 11/20/2024.
//

#include "Model.h"
#include <iostream>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "glad/glad.h"

#define ASSIMP_LOAD_FLAGS (aiProcess_Triangulate | aiProcess_GenNormals | aiProcess_JoinIdenticalVertices)


static Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene) {

    VertexData vertices;
    std::vector<unsigned int> indices;



    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        // Position
        aiVector3D position = mesh->mVertices[i];
        vertices.Positions.push_back({ position.x, position.y, position.z });

        // Normal
        if (mesh->mNormals) {
            aiVector3D normal = mesh->mNormals[i];
            vertices.Normals.push_back({ normal.x, normal.y, normal.z });
        }

        // Texture Coordinates (check for availability)
        if (mesh->mTextureCoords[0]) {
            aiVector3D uv = mesh->mTextureCoords[0][i];
            vertices.TexCoords.push_back({ uv.x, uv.y });
        } else {
            vertices.TexCoords.push_back({ 0.0f, 0.0f }); // Default UVs
        }
    }

    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }

    VertexArray vertexArray;
    VertexBuffer positionBuffer = VertexBuffer(vertices.Positions.data(), vertices.Positions.size());
    VertexBuffer normalsBuffer = VertexBuffer(vertices.Normals.data(), vertices.Normals.size());
    VertexBuffer uvBuffer = VertexBuffer(vertices.TexCoords.data(), vertices.TexCoords.size());

    IndexBuffer indexBuffer(indices.data(), indices.size());

    vertexArray.Bind();
    vertexArray.AddBuffer(positionBuffer, Coordinates, 3);
    vertexArray.AddBuffer(normalsBuffer, NormalCoords, 3);
    vertexArray.AddBuffer(uvBuffer, TexCoords, 2);



    return Mesh{vertexArray, indexBuffer, mesh->mName.C_Str()};
}

static void ProcessNode(aiNode* node, const aiScene* scene, std::vector<Mesh>& meshes)
{

    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];

        meshes.push_back(ProcessMesh(mesh, scene));
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



