//
// Created by Nazarii on 11/29/2024.
//
#pragma once
#include <string>

#include <imgui.h>
#include "Interface/FrameBuffer.h"
#include "Rendering/Scene.h"





class Panel {
    friend class EditorUI;
private:
    ImVec2 panelSize;
    bool visible = true;
public:
    enum class PanelType {
        Hierarchy,
        Properties,
        SceneView,
        RenderStats
    };
public:
    virtual ~Panel() = default;
    virtual void Draw() = 0;

    void Update();
    virtual std::string GetName() const = 0;
    virtual PanelType GetType() const = 0;

    virtual void OnResize(float nX, float nY) {}

    void SetVisible(bool visible) { this->visible = visible; }
};

#define PANEL_CLASS_TYPE(type)	static PanelType GetStaticType() { return PanelType::type; }\
                                virtual PanelType GetType() const override { return GetStaticType(); }\
                                virtual std::string GetName() const override { return #type; }


// Example panel classes
class HierarchyPanel : public Panel {
private:
    entt::entity selectedEntity;
public:
    void Draw() override;

    void SetSelectedEntity(entt::entity entity) { selectedEntity = entity;}
    entt::entity GetSelectedEntity() { return selectedEntity; }

    PANEL_CLASS_TYPE(Hierarchy)
};

class PropertiesPanel : public Panel {
private:
    entt::entity selectedEntity;
public:
    void Draw() override;



    PANEL_CLASS_TYPE(Properties)
};


class SceneViewPanel : public Panel
{
private:
    FrameBuffer* frameBuffer;
    Camera* viewCamera;
public:
    SceneViewPanel() {};
    SceneViewPanel(Camera* viewCamera, FrameBuffer* frameBuffer) : viewCamera(viewCamera) {}

    void SetViewCamera(Camera* viewCamera) { this->viewCamera = viewCamera; }
    void SetFrameBuffer(FrameBuffer* frameBuffer) { this->frameBuffer = frameBuffer; }

    void Draw() override;

    void OnResize(float nX, float nY) override;

    PANEL_CLASS_TYPE(SceneView)
};

struct FrameStats;

class RenderStatsPanel : public Panel {
private:
    FrameStats* frameStats;
public:
    RenderStatsPanel() {}
    RenderStatsPanel(FrameStats* frameStats) : frameStats(frameStats) {}

    void SetFrameStats(FrameStats* frameStats) { this->frameStats = frameStats; }

    void Draw() override;

    PANEL_CLASS_TYPE(RenderStats)
};
