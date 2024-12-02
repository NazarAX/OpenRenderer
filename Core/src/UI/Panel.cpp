//
// Created by Nazarii on 11/29/2024.
//

#include "Panel.h"

#include "Application.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <iostream>



void Panel::Update()
{
    ImVec2 currentWindowSize = ImGui::GetContentRegionAvail();

    // Check if the size has changed
    if (currentWindowSize.x != panelSize.x || currentWindowSize.y != panelSize.y)
    {
        panelSize = currentWindowSize;

        OnResize(panelSize.x, panelSize.y);
    }
}


void HierarchyPanel::Draw()
{

    ImGui::Begin(GetName().c_str());

    Update();

    std::vector<entt::entity> entities = Application::GetInstance()->GetScene()->GetEntitiesWithComponent<Name>();

    for (auto entity : entities)
    {
        // Fetch the name component
        auto& nameComponent = Application::GetInstance()->GetScene()->GetComponent<Name>(entity);

        // Create a selectable item for the entity
        if (ImGui::Selectable(nameComponent.name.c_str(), selectedEntity == entity))
        {
            // Handle selection logic
            selectedEntity = entity; // Update the selected entity
        }
    }

    ImGui::End();
}


void PropertiesPanel::Draw()
{
    ImGui::Begin(GetName().c_str());

}



void SceneViewPanel::Draw() {

    ImGui::Begin(GetName().c_str());

    Update();
    // Check if the texture ID is valid
    if (frameBuffer && frameBuffer->GetTextureId() != 0) {
        // Render the framebuffer texture
        ImGui::Image(frameBuffer->GetTextureId(),
                     ImVec2(frameBuffer->GetWidth(), frameBuffer->GetHeight()),
                     ImVec2(0, 1), ImVec2(1, 0)); // Flip texture coordinates (bottom-left to top-left)
    } else {
        ImGui::Text("Invalid framebuffer texture");
    }

    // End the ImGui window
    ImGui::End();
}

void SceneViewPanel::OnResize(float nX, float nY)
{
    viewCamera->Reset(nX, nY);
    frameBuffer->Update(nX, nY);
}

