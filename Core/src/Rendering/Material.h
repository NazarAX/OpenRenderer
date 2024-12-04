//
// Created by Nazarii on 11/25/2024.
//

#ifndef MATERIAL_H
#define MATERIAL_H
#include "Interface/Abstractions.h"

/*
 * Very simplified version of Material
 */

struct Material
{
    Texture Albedo;
    Shader Shader;
    std::string Name;
};

#endif //MATERIAL_H
