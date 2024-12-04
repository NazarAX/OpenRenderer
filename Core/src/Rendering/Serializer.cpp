//
// Created by Nazarii on 12/3/2024.
//

#include "Serializer.h"
#include <yaml-cpp/yaml.h>
#include <Utils.h>



void Serializer::Serialize(Scene* scene, const std::string& filename)
{
    YAML::Emitter emitter;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "Scene";
    emitter << YAML::BeginSeq;

    for (entt::entity entity : scene->GetEntitiesWithComponent<Name>())
    {
        emitter << YAML::BeginMap;
        emitter << YAML::Key << "Name" << YAML::Value << scene->GetComponent<Name>(entity).name;

        if (scene->HasComponent<Transform>(entity))
        {
            Transform& transform = scene->GetComponent<Transform>(entity);

            emitter << YAML::Key << "Transform" << YAML::Value << YAML::BeginMap;

            emitter << YAML::Key << "Position" << YAML::Value;
            emitter << YAML::Flow << YAML::BeginSeq;
            emitter << transform.position.x;
            emitter << transform.position.y;
            emitter << transform.position.z;
            emitter << YAML::EndSeq;

            emitter << YAML::Key << "Rotation" << YAML::Value;
            emitter << YAML::Flow << YAML::BeginSeq;
            emitter << transform.rotation.x;
            emitter << transform.rotation.y;
            emitter << transform.rotation.z;
            emitter << YAML::EndSeq;

            emitter << YAML::Key << "Scale" << YAML::Value;
            emitter << YAML::Flow << YAML::BeginSeq;
            emitter << transform.scale.x;
            emitter << transform.scale.y;
            emitter << transform.scale.z;
            emitter << YAML::EndSeq;

            emitter << YAML::EndMap;

        }

        if (scene->HasComponent<Model>(entity))
        {
            Model& model = scene->GetComponent<Model>(entity);
            emitter << YAML::Key << "Model" << YAML::Value << model.GetName();
        }

        if (scene->HasComponent<Material>(entity))
        {
            Material& material = scene->GetComponent<Material>(entity);
            emitter << YAML::Key << "Material" << YAML::Value << YAML::BeginMap;
            emitter << YAML::Key << "Albedo" << YAML::Value << material.Albedo.GetFilePath();
            emitter << YAML::Key << "Shader" << YAML::Value << material.Shader.GetName();
            emitter << YAML::EndMap;
        }


        emitter << YAML::EndMap;
    }

    emitter << YAML::EndSeq;
    emitter << YAML::EndMap;

    File::writeFile(filename, emitter.c_str());
}

Scene* Serializer::Deserialize(const std::string& filename)
{
    return nullptr;
}