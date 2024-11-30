//
// Created by Nazarii on 11/28/2024.
//

#include "Scene.h"

#include <stdexcept>
#include <utility>
#include <yaml-cpp/yaml.h>


//NOTE: NOT IMPLEMENTED YET
//TODO: Serialization be implemented later
namespace YAML {
    template<>
    struct convert<glm::vec3> {
        static Node encode(const glm::vec3& rhs)
        {
            Node node;
            node.push_back(rhs.x);
            node.push_back(rhs.y);
            node.push_back(rhs.z);
            return node;
        }

        static bool decode(const Node& node, glm::vec3& rhs) {
            if (!node.IsSequence() || node.size() != 3)
                return false;

            rhs.x = node[0].as<float>();
            rhs.y = node[1].as<float>();
            rhs.z = node[2].as<float>();
            return true;
        }
    };
}


//NOTE: NOT IMPLEMENTED YET
Scene * Scene::LoadScene(const std::string &filename)
{
    return nullptr;
}
//NOTE: NOT IMPLEMENTED YET
void Scene::SaveScene(const std::string &filename, Scene *scene)
{
    YAML::Node sceneNode;

}
