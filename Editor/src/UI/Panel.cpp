//
// Created by Nazarii on 11/29/2024.
//

#include "Panel.h"

#include "../Application.h"
#include "imgui.h"
#include "Rendering/Scene.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <entt/entt.hpp>
#include <iostream>
#include <sstream>
#include <typeindex>
#include <type_traits>







namespace EditorUI
{

    void DrawSceneViewPanel(FrameBuffer* frameBuffer, Camera* viewCamera)
    {

        ImGui::Begin("Scene View");
        static ImVec2 prevSize(0,0);

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

        ImGui::End();
    }


    void DrawSettingsPanel(FrameStats frameStats) 
    {
        ImGui::Begin("Render Stats");

        ImGui::Text(std::string("Delta Time : " + std::to_string(frameStats.DeltaTime)).c_str());

        ImGui::Text(std::string("FPS : " + std::to_string(1/frameStats.DeltaTime)).c_str());

        ImGui::End();
    }

    void DrawMainMenuBar()
    {
        if (ImGui::BeginMainMenuBar())
        {
            // File menu
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("New", "Ctrl+N")) { /* Handle New */ }
                if (ImGui::MenuItem("Open", "Ctrl+O")) { /* Handle Open */ }
                if (ImGui::MenuItem("Save", "Ctrl+S")) { /* Handle Save */ }
                ImGui::Separator();
                if (ImGui::MenuItem("Exit", "Alt+F4")) { /* Handle Exit */ }
                ImGui::EndMenu();
            }

            // Edit menu
            if (ImGui::BeginMenu("Edit"))
            {
                if (ImGui::MenuItem("Undo", "Ctrl+Z")) { /* Handle Undo */ }
                if (ImGui::MenuItem("Redo", "Ctrl+Y")) { /* Handle Redo */ }
                ImGui::Separator();
                if (ImGui::MenuItem("Cut", "Ctrl+X")) { /* Handle Cut */ }
                if (ImGui::MenuItem("Copy", "Ctrl+C")) { /* Handle Copy */ }
                if (ImGui::MenuItem("Paste", "Ctrl+V")) { /* Handle Paste */ }
                ImGui::EndMenu();
            }

            // View menu
            if (ImGui::BeginMenu("View"))
            {
                if (ImGui::MenuItem("Show Toolbar", NULL, true)) { /* Handle Toolbar Toggle */ }
                if (ImGui::MenuItem("Show Sidebar", NULL, true)) { /* Handle Sidebar Toggle */ }
                ImGui::EndMenu();
            }

            ImGui::EndMainMenuBar();
        }
    }



    void DrawPropertiesPanel(Scene* scene, entt::entity& selected)
    {
        ImGui::Begin("Properties");

        std::vector<std::type_index> missingComponents;
        if (scene->HasComponent<Name>(selected))
        {
            auto& name = scene->GetComponent<Name>(selected).name;

            static char buffer[256];
            memset(buffer, 0, 256);
            strcpy(buffer, name.c_str());

            if (ImGui::InputText("Name", buffer, 256)) {
                name = buffer;
            }
        }

        if (scene->HasComponent<Transform>(selected))
        {
            Transform& transform = scene->GetComponent<Transform>(selected);

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
        else
        {
            missingComponents.push_back(typeid(Transform));
        }

        if (scene->HasComponent<Model>(selected))
        {
            Model& model = scene->GetComponent<Model>(selected);

            if (ImGui::TreeNodeEx("Mesh"))
            {
                ImGui::Text(std::string("Mesh "  + model.GetName()).c_str());

                ImGui::TreePop();
            }
        }
        else
        {
            missingComponents.push_back(typeid(Model));
        }

        if (scene->HasComponent<Material>(selected))
        {
            Material& material = scene->GetComponent<Material>(selected);

            if (ImGui::TreeNodeEx("Material"))
            {
                ImGui::Text(material.Name.c_str());

                ImGui::Text("Albedo");
                ImGui::Image(material.Albedo.GetId(), ImVec2(100, 100));


                ImGui::TreePop();
            }
        }
        else
        {
            missingComponents.push_back(typeid(Material));
        }
        
        if (ImGui::BeginPopup("Components"))
        {

            
            ImGui::EndPopup();
        }

        if (ImGui::Button("Add Component"))
        {
            ImGui::OpenPopup("Components");
        }

        ImGui::End();
    }





    void DrawHierarchyPanel(Scene* scene, entt::entity& selected)
    {

        ImGui::Begin("Hierarchy");

        entt::entity hovered;

        std::cout << "nameComponent.name";
        scene->GetRegistry().each([scene, &selected, &hovered](auto entity)
        {
            auto& nameComponent = scene->GetComponent<Name>(entity);

            // Create a selectable item for the entity
            if (ImGui::Selectable(nameComponent.name.c_str(), selected == entity))
            {
                // Handle selection logic
                selected = entity; // Update the selected entity
            }

            if (ImGui::IsItemHovered() && ImGui::IsMouseDown(1))
            {
                hovered = entity;
            }
        });


        if (ImGui::BeginPopup("RightClickPopup")) // Check if the popup is open
        {
            if (ImGui::MenuItem("Delete")) // Add a "Delete" menu item
            {
                if (hovered != entt::null)
                {
                    // Handle deletion of the hovered entity
                    scene->DeleteEntity(hovered);  // Delete the entity from the registry
                    hovered = entt::null;  // Reset hovered entity after deletion
                }
            }

            if (ImGui::MenuItem("Deactivate")) // Add a "Deactivate" menu item
            {
                if (hovered != entt::null)
                {
                    // Handle deactivation of the hovered entity (you can add your deactivation logic here)
                    // Example: scene->DeactivateEntity(hovered);
                    hovered = entt::null;  // Reset hovered entity after deactivation
                }
            }

            ImGui::EndPopup(); // End the popup
        }

        if (ImGui::Button("Create Empty Entity"))
        {
            scene->CreateEntity("Empty");
        }


        ImGui::End();

        if (selected != entt::null) 
        {
            DrawPropertiesPanel(scene, selected);
        }
    }
}