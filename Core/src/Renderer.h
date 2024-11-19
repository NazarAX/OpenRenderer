#pragma once
#include "Rendering/Abstractions.h"
#include "Rendering/Buffers.h"
#include <memory>

struct Transform
{
	glm::vec3 position;
	glm::vec3 rotation;
};



class Camera
{
private:
	glm::vec3 pos;
	glm::mat4 projection;
	glm::mat4 view;
private:
	void calculateView();
public:
	Camera() {}
	Camera(float w, float h, float fov);

	void reset(float width, float height, float fov = 45.0f);
	void move(glm::vec3 delta);
	void setPosition(glm::vec3 _pos);

	glm::vec3 getPosition() { return this->pos; }
	glm::mat4 getView() const { return view; }
	glm::mat4 getProjection() const { return projection; }
	static glm::mat4 getModel(glm::vec3 position, glm::vec3 rotation = glm::vec3(0), glm::vec3 scale = glm::vec3(1));
};






class Renderer
{
public:
	Renderer();
	~Renderer() {}

	void beginScene(std::shared_ptr<Camera> camera);
	void draw(VertexArray& va, Shader& shader, IndexBuffer& ib);
	void draw(VertexArray& va, Shader& shader, IndexBuffer& ib, Transform position);
	void drawQuad(Shader& shader);
	void drawQuad(Shader& shader, Transform transform);
	void endScene();
public:
	VertexArray quadVA;
	IndexBuffer quadIB;
	std::shared_ptr<Camera> camera;
};

