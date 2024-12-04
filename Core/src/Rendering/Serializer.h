//
// Created by Nazarii on 12/3/2024.
//

#ifndef SERIALIZER_H
#define SERIALIZER_H

#include "Scene.h"


class Serializer
{
public:
    static void Serialize(Scene* scene, const std::string& filename);
    static Scene* Deserialize(const std::string& filename);
};



#endif //SERIALIZER_H
