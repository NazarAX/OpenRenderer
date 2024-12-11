// //
// // Created by Nazarii on 11/25/2024.
// //
//
// #ifndef USERINTERFACE_H
// #define USERINTERFACE_H
// #include <iostream>
//
// #include <imgui.h>
// #include <System/Window.h>
// #include <Rendering/Scene.h>
// #include "Panel.h"
// #include <Interface/FrameBuffer.h>
//
//
// struct EditorInfo
// {
//     Camera* ViewCamera;
//     FrameBuffer* FrameBuffer;
//     entt::entity SelectedEntity;
// };
//
//
// class EditorUI
// {
// private:
//     std::vector<std::shared_ptr<Panel>> panels;
//     EditorInfo* editorInfo;
//     static EditorUI* instance;
// public:
//     void AddPanel(std::shared_ptr<Panel> _panel)
//     {
//         for (auto panel : panels) {
//             if (panel->GetType() == _panel->GetType()) {
//                 std::cerr << "Panel " << _panel->GetName() << " already added" << std::endl;
//                 return;
//             }
//         }
//         panels.push_back(_panel);
//     }
// private:
//     EditorUI();
// public:
//     ~EditorUI();
//
//
//     void SetDarkTheme();
//
//     static EditorUI* GetInstance() {
//         if (instance == nullptr) {
//             instance = new EditorUI();
//         }
//         return instance;
//     }
//
//     void SetEditorInfo(EditorInfo* _editorInfo);
//     EditorInfo* GetEditorInfo() { return editorInfo; }
//
//     template<class T>
//     void SetPanelVisible(bool status) {
//         static_assert(std::is_base_of<Panel, T>::value, "T must derive from Panel");
//
//         for (auto panel : panels) {
//             if (panel->GetType() == T::GetStaticType()) {
//                 panel->SetVisible(status);
//             }
//         }
//     }
//
//     template<class T>
// T* GetPanel()
//     {
//         static_assert(std::is_base_of<Panel, T>::value, "T must derive from Panel");
//
//         for (const auto& panel : panels) {  // Use `const auto&` for safety with unique_ptr
//             if (panel->GetType() == T::GetStaticType()) {
//                 return static_cast<T*>(panel.get());  // Cast to the derived type
//             }
//         }
//
//         return nullptr;  // Explicitly return nullptr if not found
//     }
//
//
//     void Draw();
// };
//
//
//
// #endif //USERINTERFACE_H


#include <functional>

namespace UI
{
    void Init();
    void Begin();
    void End();
    void SetDarkTheme();

    //Make sure to call right after drawing element
    void FileReplaceableItem(const char** filters, std::function<void(std::string)> onReplace);
}
