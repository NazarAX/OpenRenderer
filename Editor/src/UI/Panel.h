//
// Created by Nazarii on 11/29/2024.
//
#pragma once
#include <string>

#include <imgui.h>
#include "Interface/FrameBuffer.h"
#include "Rendering/Scene.h"



//
//
// class Panel {
//     friend class EditorUI;
// private:
//     ImVec2 panelSize;
//     bool visible = true;
// public:
//     enum class PanelType {
//         Hierarchy,
//         Properties,
//         SceneView,
//         RenderStats
//     };
// public:
//     virtual ~Panel() = default;
//     virtual void Draw() = 0;
//
//     void Update();
//     virtual std::string GetName() const = 0;
//     virtual PanelType GetType() const = 0;
//
//     virtual void OnResize(float nX, float nY) {}
//
//     void SetVisible(bool visible) { this->visible = visible; }
// };
//
// #define PANEL_CLASS_TYPE(type)	static PanelType GetStaticType() { return PanelType::type; }\
//                                 virtual PanelType GetType() const override { return GetStaticType(); }\
//                                 virtual std::string GetName() const override { return #type; }


// Example panel classes


struct FrameStats;


class HierarchyPanel
{
private:
    entt::entity selectedEntity;
public:
    void Draw();

    void SetSelectedEntity(entt::entity entity) { selectedEntity = entity;}
    entt::entity GetSelectedEntity() { return selectedEntity; }

};


class SceneViewPanel
{
private:
    ImVec2 prevSize;
public:
    void Draw(FrameBuffer* frameBuffer, Camera* camera);
};

class SettingsPanel
{
public:
    void Draw(FrameStats frameStats);
};


