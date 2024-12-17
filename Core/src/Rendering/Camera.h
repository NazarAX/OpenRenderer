//
// Created by Nazarii on 11/25/2024.
//

#ifndef CAMERA_H
#define CAMERA_H

#include <memory>
#include "Interface/FrameBuffer.h"
#include "Components.h"



class Camera
{
private:
    Transform transform;
    glm::mat4 projection;
    glm::mat4 view;

    glm::vec3 front;
    glm::vec3 up;
    bool primary;
public:
    Camera() : up(0, 1, 0) {}
    Camera(bool _primary)  : primary(_primary), up(0, 1, 0) {}
    Camera(float w, float h, float fov, bool primary);

    void Reset(float width, float height, float fov = 90.0f);
    void UpdateView(Transform& transform);

    void SetZoom(float zoom);

    Transform GetTransform() { return transform; }


    bool IsPrimary() { return primary; }
    void SetPrimary(bool _primary) { primary = _primary; }

    glm::vec3 GetRight() const { return glm::cross(front, up); }
    glm::vec3 GetFront() const { return front; }

    glm::mat4 GetView() const { return view; }
    glm::mat4 GetProjection() const { return projection; }
};


class CameraController
{
private:
    Camera& camera;
    Transform& transform;
    float sensitivity;

public:
    CameraController(Camera& _camera, Transform& _transform, float _sensitivity)
    : camera(_camera), transform(_transform), sensitivity(_sensitivity) {}

    ~CameraController() {}

    void Update();
    float GetSensitivity() const { return sensitivity; }
};




#endif //CAMERA_H
