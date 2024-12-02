//
// Created by Nazarii on 11/25/2024.
//

#include "Camera.h"


#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <iostream>
#include <ostream>
#include <glm/gtx/string_cast.hpp>
#include <vector>
#include "Interface/Exception.h"
#include "Model.h"
#include "System/Input.h"


Camera::Camera(float w, float h, float fov)
{
	transform = CameraTransform
	{
		glm::vec3(0, 0, 0),
		glm::vec3(0, 0, 0),
		glm::vec3(0, 1, 0),
		1,
		0,
		90
	};

	float nearPlane = 0.1f; // Near clipping plane
	float farPlane = 100.0f; // Far clipping plane

	float aspectRatio = (float)w / (float)h;
	this->projection = glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);

}

void Camera::UpdateView()
{
	transform.front.x = cos(glm::radians(transform.yaw)) * cos(glm::radians(transform.pitch));
	transform.front.y = sin(glm::radians(transform.pitch));
	transform.front.z = sin(glm::radians(transform.yaw)) * cos(glm::radians(transform.pitch));

	glm::vec3 target = transform.pos + glm::normalize(transform.front); // Assuming the camera looks down the negative Z-axis

	this->view = glm::lookAt(transform.pos, target, transform.up);
}


void Camera::Reset(float width, float height, float fov) {

	float nearPlane = 0.1f; // Near clipping plane
	float farPlane = 100.0f; // Far clipping plane

	float aspectRatio = (float)width / (float)height;
	this->projection = glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);

	//
	// if (frameBuffer != nullptr)
	// 	frameBuffer->Update(width, height);
}

void Camera::SetPosition(glm::vec3 _pos)
{
	transform.pos = _pos;
	UpdateView();
}

void Camera::SetZoom(float zoom)
{
	transform.zoom = zoom;
}

void Camera::SetYaw(float _yaw)
{
	transform.yaw = _yaw;
	UpdateView();
}

void Camera::Turn(float delta_pitch, float delta_yaw)
{
	transform.pitch += glm::radians(delta_yaw);
	transform.yaw += glm::radians(delta_pitch);
	UpdateView();
}

void Camera::SetPitch(float _pitch)
{
	transform.pitch = _pitch;
	UpdateView();
}

glm::mat4 Camera::GetModel(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
	glm::mat4 model = glm::mat4(1.0f); // Identity matrix

	// Translate the model (last)
	model = glm::translate(model, position);

	// Rotate the model (second)
	model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1, 0, 0)); // Rotate around X
	model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0, 1, 0)); // Rotate around Y
	model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0, 0, 1)); // Rotate around Z

	// Scale the model (first)
	model = glm::scale(model, scale);

	return model;
}


void CameraController::UpdateInputs()
{
	// Handle input
	if (Input::isKeyDown(Input::KeyCode::W)) camera->Move(camera->GetFront() * 0.1f);
	if (Input::isKeyDown(Input::KeyCode::S)) camera->Move(-camera->GetFront() * 0.1f );
	if (Input::isKeyDown(Input::KeyCode::D)) camera->Move(camera->GetRight() * 0.1f);
	if (Input::isKeyDown(Input::KeyCode::A)) camera->Move(-camera->GetRight() * 0.1f);


	if (Input::isMouseButtonPressed(Input::MouseCode::Button1) )
	{
		camera->Turn(Input::getMouseDelta().x * 2, Input::getMouseDelta().y * 2);
	}
}

void Camera::Move(glm::vec3 _pos)
{
	transform.pos += _pos;
	UpdateView();
}
