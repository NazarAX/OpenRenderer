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


class UserInterface
{
private:
    std::vector<std::shared_ptr<Panel>> panels;
    ImGuiIO* io;
    Window* window;
    Scene* scene;
public:
    UserInterface(Window* window);
    ~UserInterface();


    void AddPanel(std::shared_ptr<Panel> panel)
    {
        panels.push_back(panel);
    }


    void Draw(FrameBuffer* buffer);
};



#endif //USERINTERFACE_H
