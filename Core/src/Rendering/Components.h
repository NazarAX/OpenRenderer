//
// Created by Nazarii on 12/13/24.
//

#ifndef COMPONENTS_H
#define COMPONENTS_H
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>

struct Transform
{
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale = glm::vec3(1.0f);

    glm::mat4 GetModel() const
    {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, position);
        model = model * glm::mat4_cast(glm::quat(rotation)); // Convert Euler angles to quaternion for rotation
        model = glm::scale(model, scale);
        return model;
    }

};

struct Name
{
    std::string name;
};


#endif //COMPONENTS_H
