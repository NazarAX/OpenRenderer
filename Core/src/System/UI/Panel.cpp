//
// Created by Nazarii on 11/29/2024.
//

#include "Panel.h"

#include "Application.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"




void HierarchyPanel::Draw()
{

    ImGui::Begin(GetName().c_str());

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