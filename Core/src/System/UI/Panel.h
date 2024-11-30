//
// Created by Nazarii on 11/29/2024.
//
#pragma once
#include <string>
#include "Rendering/Scene.h"



class Panel {
    friend class UserInterface;
public:
    virtual ~Panel() = default;
    virtual void Draw() = 0;

    virtual std::string GetName() = 0;
};

// Example panel classes
class HierarchyPanel : public Panel {
    friend class UserInterface;
private:
    entt::entity selectedEntity;
public:
    void Draw() override;

    std::string GetName() override { return "Hierarchy"; }
};

class PropertiesPanel : public Panel {
    friend class UserInterface;
public:
    void Draw() override;

    std::string GetName() override { return "Properties"; }
};