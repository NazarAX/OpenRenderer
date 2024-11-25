#pragma once
#include "Interface/Abstractions.h"
#include "Interface/Buffers.h"
#include "Camera.h"
#include <memory>

#include "Model.h"




class Renderer
{
public:
	Renderer();
	~Renderer() {}

	void SetupShaderUniforms(Material &material, Transform transform);

	void BeginScene(std::shared_ptr<Camera> camera);
	void DrawQuad(Shader& shader);
	void DrawModel(const Model& model);
	void EndScene();
public:
	Material material;
	VertexArray quadVA;
	IndexBuffer quadIB;
	std::shared_ptr<Camera> camera;
};

