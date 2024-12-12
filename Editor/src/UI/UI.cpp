//
// Created by Nazarii on 11/25/2024.
//

#include "UI.h"

#include <iostream>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "GLFW/glfw3.h"
#include "System/Window.h"
#include <tinyfiledialogs.h>

namespace UI
{

    void Init()
    {
        //ImGui initialization
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        //io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

        
        float fontSize = 22.0f;

        float xscale, yscale;
        glfwGetWindowContentScale(Window::currentWindow->GetHandle(), &xscale, &yscale);

        io.Fonts->AddFontFromFileTTF("res/fonts/TitilliumWeb-Bold.ttf", fontSize * xscale);
        io.FontDefault = io.Fonts->AddFontFromFileTTF("res/fonts/TitilliumWeb-Regular.ttf", fontSize * xscale);
 



        int fbWidth, fbHeight;
        int winWidth, winHeight;
        glfwGetFramebufferSize(Window::currentWindow->GetHandle(), &fbWidth, &fbHeight);
        glfwGetWindowSize(Window::currentWindow->GetHandle(), &winWidth, &winHeight);
        io.DisplayFramebufferScale = ImVec2((float)fbWidth / winWidth, (float)fbHeight / winHeight);

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        SetDarkTheme();
        ImGui_ImplOpenGL3_Init();
        ImGui_ImplGlfw_InitForOpenGL(Window::currentWindow->GetHandle(), true);
    }

    void Begin()
    {
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGui::DockSpaceOverViewport();
    }

    void End()
    {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        ImGuiIO& io = ImGui::GetIO();

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            

            // Restore the OpenGL rendering context to the main window DC, since platform windows might have changed it.
            glfwMakeContextCurrent(Window::currentWindow->GetHandle());
        }
    }

    void SetDarkTheme()
    {
        ImVec4* colors = ImGui::GetStyle().Colors;
        colors[ImGuiCol_FrameBg]                = ImVec4(0.27f, 0.27f, 0.28f, 0.54f);
        colors[ImGuiCol_WindowBg]               = ImVec4(0.11f, 0.11f, 0.11f, 0.84f);

        colors[ImGuiCol_TitleBg] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
        colors[ImGuiCol_TitleBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
        colors[ImGuiCol_TitleBgCollapsed] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
    }
}
