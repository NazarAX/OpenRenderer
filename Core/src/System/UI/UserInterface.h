//
// Created by Nazarii on 11/25/2024.
//

#ifndef USERINTERFACE_H
#define USERINTERFACE_H
#include "System/Window.h"
#include "Rendering/Scene.h"
#include "Panel.h"







class UserInterface
{
private:
    std::vector<std::unique_ptr<Panel>> panels;
public:
    UserInterface(Window window);
    ~UserInterface();

    template <class T, class... Args>
    T& AddPanel(Args&&... args) {
        static_assert(std::is_base_of<Panel, T>::value, "T must derive from Panel");
        panels.push_back(std::make_unique<T>(std::forward<Args>(args)...));
        return *static_cast<T*>(panels.back().get());
    }

    template <typename T>
    T& GetPanel(){
        static_assert(std::is_base_of<Panel, T>::value, "T must derive from Panel");

        for (const auto& panel : panels)
        {
            if (auto result = dynamic_cast<T&>(panel.get()))
            {
                return *result; // Return pointer to the panel if found
            }
        }

        return nullptr;
    }



    void Draw();
};



#endif //USERINTERFACE_H
