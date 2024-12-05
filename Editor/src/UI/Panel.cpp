//
// Created by Nazarii on 11/29/2024.
//

#include "Panel.h"

#include "../Application.h"
#include "imgui.h"
#include "Rendering/Scene.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <iostream>
#include <sstream>




void HierarchyPanel::Draw()
{

    ImGui::Begin("Hierarchy");
    Scene* scene = Application::GetInstance()->GetScene();

    std::vector<entt::entity> entities = scene->GetEntitiesWithComponent<Name>();

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

    if (selectedEntity != entt::null) {
        ImGui::Begin("Properties");

        if (scene->HasComponent<Name>(selectedEntity))
        {
            auto& name = scene->GetComponent<Name>(selectedEntity).name;

            static char buffer[256];
            memset(buffer, 0, 256);
            strcpy(buffer, name.c_str());

            if (ImGui::InputText("Name", buffer, 256)) {
                name = buffer;
            }
        }

        if (scene->HasComponent<Transform>(selectedEntity))
        {
            Transform& transform = scene->GetComponent<Transform>(selectedEntity);

            if (ImGui::TreeNodeEx("Transform"))
            {
                // Position
                ImGui::DragFloat3("Position", &transform.position.x, 0.1f);

                // Rotation
                ImGui::DragFloat3("Rotation", &transform.rotation.x, 1.0f);

                // Scale
                ImGui::DragFloat3("Scale", &transform.scale.x, 0.1f);

                ImGui::TreePop();
            }
        }

        if (scene->HasComponent<Model>(selectedEntity))
        {
            Model& model = scene->GetComponent<Model>(selectedEntity);

            if (ImGui::TreeNodeEx("Mesh"))
            {
                ImGui::Text(std::string("Mesh "  + model.GetName()).c_str());

                ImGui::TreePop();
            }
        }

        if (scene->HasComponent<Material>(selectedEntity))
        {
            Material& material = scene->GetComponent<Material>(selectedEntity);

            if (ImGui::TreeNodeEx("Material"))
            {
                ImGui::Text(material.Name.c_str());

                ImGui::Text("Albedo");
                ImGui::Image(material.Albedo.GetId(), ImVec2(100, 100));


                ImGui::TreePop();
            }
        }



        



        if (ImGui::BeginPopupContextItem("Components"))
        {
            if (ImGui::MenuItem("Option 1")) { /* Handle Option 1 */ }
            if (ImGui::MenuItem("Option 2")) { /* Handle Option 2 */ }
            if (ImGui::MenuItem("Option 3")) { /* Handle Option 3 */ }
            ImGui::EndPopup();
        }

        // Right-click detection to open the popup
        if (ImGui::Button("Add Component"))
        {
            ImGui::OpenPopup("Components");
        }

        ImGui::End();
    }

    ImGui::End();
}



void SceneViewPanel::Draw(FrameBuffer* frameBuffer, Camera* viewCamera)
{

    ImGui::Begin("Scene View");

    // Check if the size has changed

    ImVec2 currentPanelSize = ImGui::GetContentRegionAvail();

    if (currentPanelSize.x != prevSize.x || currentPanelSize.y !=  prevSize.y)
    {
         prevSize = currentPanelSize;

        viewCamera->Reset(currentPanelSize.x, currentPanelSize.y);
        frameBuffer->Update(currentPanelSize.x, currentPanelSize.y);
    }

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



void SettingsPanel::Draw(FrameStats frameStats) {
    ImGui::Begin("Render Stats");

    ImGui::Text(std::string("Delta Time : " + std::to_string(frameStats.DeltaTime)).c_str());

    ImGui::Text(std::string("FPS : " + std::to_string(1/frameStats.DeltaTime)).c_str());

    ImGui::End();
}