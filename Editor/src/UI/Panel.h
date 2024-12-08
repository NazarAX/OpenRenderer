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


namespace EditorUI
{
    void DrawMainMenuBar();
    void DrawSettingsPanel(FrameStats frameStats);
    void DrawHierarchyPanel(Scene* scene, entt::entity& selected);
    void DrawSceneViewPanel(FrameBuffer* frameBuffer, Camera* viewCamera);
}  
