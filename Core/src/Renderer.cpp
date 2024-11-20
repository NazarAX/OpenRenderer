#include "Renderer.h"
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
#include <vector>
#include "Exception.h"





Camera::Camera(float w, float h, float fov) :
	pos(0, 0, 0)
{
	reset(w, h, fov);
}

void Camera::calculateView()
{
	glm::mat4 translation = glm::translate(glm::mat4(1), this->pos);
	glm::vec3 target = pos + glm::vec3(0, 0, 1); // Assuming the camera looks down the negative Z-axis
	glm::vec3 up = glm::vec3(0, 1, 0); // Assuming Y is up
	this->view = glm::lookAt(pos, target, up);
}


void Camera::reset(float width, float height, float fov) {

	float nearPlane = 0.1f; // Near clipping plane
	float farPlane = 100.0f; // Far clipping plane

	float aspectRatio = (float)width / (float)height;
	this->projection = glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
}

void Camera::setPosition(glm::vec3 _pos)
{
	this->pos = _pos;
	calculateView();
}

glm::mat4 Camera::getModel(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
	glm::mat4 model = glm::mat4(1.0f); // Identity matrix

	// Scale the model
	model = glm::scale(model, scale);

	// Rotate the model
	model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0, 0, 1)); // Rotate around Z
	model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0, 1, 0)); // Rotate around Y
	model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1, 0, 0)); // Rotate around X

	// Translate the model
	model = glm::translate(model, position);

	return model;
}

void Camera::move(glm::vec3 _pos)
{
	this->pos += _pos;
	calculateView();
}






Renderer::Renderer()
{
	float quadVertices[] = {
		// Position       // TexCoords
		-1.0f,  1.0f,    0.0f, 0.0f, // Top-left (Y flipped)
		-1.0f, -1.0f,    0.0f, 1.0f, // Bottom-left
		 1.0f, -1.0f,    1.0f, 1.0f, // Bottom-right
		 1.0f,  1.0f,    1.0f, 0.0f  // Top-right (Y flipped)
	};

	unsigned int quadIndices[] = {
		0, 1, 2, // First triangle
		0, 2, 3  // Second triangle
	};

	VertexLayout layout = {2, 0, 2};  // Position: 2 floats, TexCoords: 2 floats
	// quadVA = VertexArray(quadVertices, sizeof(quadVertices), layout);
	// quadIB = IndexBuffer(quadIndices, 6);

	glEnable(GL_POLYGON_OFFSET_FILL);
	glPolygonOffset(1.0f, 1.0f); // Adjust the values as needed
}



void Renderer::draw(VertexArray& va, Shader& shader, IndexBuffer& ib)
{
	va.Bind();
	shader.bind();
	ib.Bind();


	GL(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, 0));
}

void Renderer::draw(VertexArray& va, Shader& shader, IndexBuffer& ib, Transform transform)
{
	va.Bind();
	shader.bind();

	glm::mat4 modelMatrix = Camera::getModel(transform.position, transform.rotation);
	shader.setUniformMatrix4fv("model", modelMatrix);
	shader.setUniformMatrix4fv("view", camera->getView());
	shader.setUniformMatrix4fv("projection", camera->getProjection());

	GL(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, 0));
}

void Renderer::drawQuad(Shader& shader)
{
	
	quadVA.Bind();
	shader.bind();
	quadIB.Bind();

	GL(glDrawElements(GL_TRIANGLES, quadIB.GetCount(), GL_UNSIGNED_INT, 0));
}

void Renderer::drawQuad(Shader& shader, Transform transform)
{
	shader.bind();
	glm::mat4 modelMatrix = Camera::getModel(transform.position, transform.rotation);
	shader.setUniformMatrix4fv("model", modelMatrix);
	shader.setUniformMatrix4fv("view", camera->getView());
	shader.setUniformMatrix4fv("projection", camera->getProjection());

	draw(quadVA, shader, quadIB);
}

void Renderer::beginScene(std::shared_ptr<Camera> camera)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0);

	this->camera = camera;
}

void Renderer::endScene() 
{
	
}