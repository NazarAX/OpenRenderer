//
// Created by Nazarii on 11/25/2024.
//

#ifndef USERINTERFACE_H
#define USERINTERFACE_H
#include "imgui.h"
#include "System/Window.h"
#include "Rendering/Scene.h"
#include "Panel.h"
#include "Interface/FrameBuffer.h"


struct EditorInfo
{
    Window* Window;
    Scene* Scene;
    Camera* ViewCamera;
    FrameBuffer* FrameBuffer;
};


class EditorUI
{
private:
    std::vector<std::shared_ptr<Panel>> panels;
    ImGuiIO* io;
    EditorInfo editorInfo;
private:
    void AddPanel(std::shared_ptr<Panel> panel)
    {
        panels.push_back(panel);
    }
public:
    EditorUI(EditorInfo info);
    ~EditorUI();




    template<class T>
    void SetPanelVisible(bool status) {
        static_assert(std::is_base_of<Panel, T>::value, "T must derive from Panel");

        for (auto panel : panels) {
            if (panel->GetType() == T::GetStaticType()) {
                panel->SetVisible(status);
            }
        }
    }

    template<class T>
    std::shared_ptr<T> GetPanel()
    {
        static_assert(std::is_base_of<Panel, T>::value, "T must derive from Panel");

        for (auto panel : panels) {
            if (panel->GetType() == T::GetStaticType()) {
                return panel.get();
            }
        }
    }


    void Draw();
};



#endif //USERINTERFACE_H
