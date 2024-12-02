//
// Created by Nazarii on 11/25/2024.
//

#include "EditorUI.h"

#include <iostream>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "GLFW/glfw3.h"
#include "System/Window.h"




EditorUI::EditorUI(EditorInfo info) : editorInfo(info)
{
    //ImGui initialization
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    io = &ImGui::GetIO();
    io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io->ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    ImGui_ImplOpenGL3_Init();
    ImGui_ImplGlfw_InitForOpenGL(info.Window->GetHandle(), true);


    std::shared_ptr<HierarchyPanel> hierarchy_panel = std::make_shared<HierarchyPanel>();
    std::shared_ptr<SceneViewPanel> scene_view_panel = std::make_shared<SceneViewPanel>();

    scene_view_panel->SetViewCamera(info.ViewCamera);
    scene_view_panel->SetFrameBuffer(info.FrameBuffer);


    AddPanel(hierarchy_panel);
    AddPanel(scene_view_panel);
}

EditorUI::~EditorUI()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void EditorUI::Draw()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGui::DockSpaceOverViewport();

    for (const auto& panel : panels)
    {
        panel->Draw();
    }



    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();

        // Restore the OpenGL rendering context to the main window DC, since platform windows might have changed it.
        glfwMakeContextCurrent(editorInfo.Window->GetHandle());
    }
}
