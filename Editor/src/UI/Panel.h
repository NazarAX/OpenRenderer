//
// Created by Nazarii on 11/29/2024.
//
#pragma once
#include <string>

#include <imgui.h>
#include "Interface/FrameBuffer.h"
#include "Rendering/Scene.h"


struct FrameStats;


namespace UI
{
    void DrawMainMenuBar();
    void DrawSettingsPanel(FrameStats frameStats);
    void DrawHierarchyPanel(Scene* scene, entt::entity& selected);
    void DrawSceneViewPanel(FrameBuffer* frameBuffer, Camera& viewCamera, entt::entity selected, Scene* scene);


}  
