//
// Created by Nazarii on 11/28/2024.
//

#ifndef SCENE_H
#define SCENE_H
#include "Model.h"
#include <glm/glm.hpp>
#include <entt/entt.hpp>
#include <stdexcept>
#include <string>

#include "System/Input.h"

struct Transform
{
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;


    //static glm::mat4 GetModelMatrix(Transform&, std::shared_ptr<Camera>);
};

struct Name
{
    std::string name;
};

class Scene
{
private:
    entt::registry registry;
    std::string name;
public:
    Scene() : name("Unnamed scene") {}
    Scene(std::string  name) : name(std::move(name)) {}
    ~Scene() {}
public:
    entt::entity CreateEntity(const std::string& name)
    {
        auto entity = registry.create();
        registry.emplace<Name>(entity, name);
        return entity;
    }

    entt::entity GetEntity(const std::string& name) const
    {
        for (entt::entity entity : registry.view<Name>())
        {
            if (registry.get<Name>(entity).name == name)
                return entity;
        }
        return entt::null;
    }


    entt::registry& GetRegistry() { return registry; }

    template<typename T,typename... Args> T& AddComponent(entt::entity entity,Args&&... args)
    {
        registry.emplace<T>(entity, std::forward<Args>(args)...);
        return registry.get<T>(entity);
    }

    template<typename T>
    void RemoveComponent(entt::entity entity)
    {
        registry.remove<T>(entity);
    }

    template<typename T>
    T& GetComponent(entt::entity entity)
    {
        if (registry.all_of<T>(entity))
            return registry.get<T>(entity);
        throw std::runtime_error("Entity does not have the requested component.");
    }

    template<typename T>
    bool HasComponent(entt::entity entity) {
        if (registry.all_of<T>(entity))
            return true;
        return false;
    }

    template<typename T>
    std::vector<entt::entity> GetEntitiesWithComponent() const
    {
        std::vector<entt::entity> result;
        result.reserve(registry.size());
        for (entt::entity entity : registry.view<T>())
            result.push_back(entity);
        return result;
    }

    std::string GetName() { return name; }
};



#endif //SCENE_H
