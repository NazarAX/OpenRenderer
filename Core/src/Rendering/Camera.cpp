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

	reset(w, h, fov=90);
}

void Camera::updateView()
{
	transform.front.x = cos(glm::radians(transform.yaw)) * cos(glm::radians(transform.pitch));
	transform.front.y = sin(glm::radians(transform.pitch));
	transform.front.z = sin(glm::radians(transform.yaw)) * cos(glm::radians(transform.pitch));

	glm::vec3 target = transform.pos + glm::normalize(transform.front); // Assuming the camera looks down the negative Z-axis

	this->view = glm::lookAt(transform.pos, target, transform.up);
}


void Camera::reset(float width, float height, float fov) {

	float nearPlane = 0.1f; // Near clipping plane
	float farPlane = 100.0f; // Far clipping plane

	float aspectRatio = (float)width / (float)height;
	this->projection = glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
}

void Camera::setPosition(glm::vec3 _pos)
{
	transform.pos = _pos;
	updateView();
}

void Camera::setZoom(float zoom)
{
	transform.zoom = zoom;
}

void Camera::setYaw(float _yaw)
{
	transform.yaw = _yaw;
	updateView();
}

void Camera::turn(float delta_pitch, float delta_yaw)
{
	transform.pitch += glm::radians(delta_yaw);
	transform.yaw += glm::radians(delta_pitch);
	updateView();
}

void Camera::setPitch(float _pitch)
{
	transform.pitch = _pitch;
	updateView();
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
	if (Input::isKeyDown(KeyCode::W)) camera->move(camera->getFront() * 0.1f);
	if (Input::isKeyDown(KeyCode::S)) camera->move(-camera->getFront() * 0.1f );
	if (Input::isKeyDown(KeyCode::D)) camera->move(camera->getRight() * 0.1f);
	if (Input::isKeyDown(KeyCode::A)) camera->move(-camera->getRight() * 0.1f);


	if (Input::isMouseButtonPressed(MouseCode::Button1) )
	{
		camera->turn(Input::getMouseDelta().x * 2, Input::getMouseDelta().y * 2);
	}
}

void Camera::move(glm::vec3 _pos)
{
	transform.pos += _pos;
	updateView();
}
