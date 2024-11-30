#include "Renderer.h"
#include <glad/glad.h>
#include "Interface/Exception.h"
#include "GLFW/glfw3.h"
#include <iostream>






Renderer::Renderer()
	: sceneLight()
{

	float quadVertices[] = {
		// Position
		-1.0f,  1.0f,
		-1.0f, -1.0f,
		 1.0f, -1.0f,
		 1.0f,  1.0f,
	};

	float quadUV[] ={
		0.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f
	};

	unsigned int quadIndices[] = {
		0, 1, 2, // First triangle
		0, 2, 3  // Second triangle
	};

	quadIB = IndexBuffer(quadIndices, 6);
	VertexBuffer uvBuffer =VertexBuffer(quadUV, sizeof(quadUV));
	VertexBuffer vertBuffer = VertexBuffer(quadVertices, sizeof(quadVertices));

	quadVA.AddBuffer(vertBuffer, Coordinates, 2);
	quadVA.AddBuffer(uvBuffer, TexCoords, 2);

	material.Shader = Shader("res/shaders/modelShader.glsl");
	material.Texture = Texture("res/textures/snail_color.png");

	// light.Color = glm::vec3(1.0f);
	// light.Position = glm::vec3(1.0f, 1.0f, 1.0f);
	// light.Intensity = 1;

	glEnable(GL_POLYGON_OFFSET_FILL);
	glPolygonOffset(1.0f, 1.0f); // Adjust the values as needed

}


void Renderer::DrawQuad(Shader& shader)
{

	quadVA.Bind();
	shader.Bind();
	quadIB.Bind();


	GL(glDrawElements(GL_TRIANGLES, quadIB.GetCount(), GL_UNSIGNED_INT, 0));
}


void Renderer::DrawModel(const Model& model, const Transform& transform)
{
	std::vector<Mesh> meshes = model.GetMeshes();

	for (Mesh mesh : meshes)
	{
		mesh.vertexArray.Bind();
		mesh.indexBuffer.Bind();

		SetupShaderUniforms(material, transform);

		glDrawElements(GL_TRIANGLES, mesh.indexBuffer.GetCount(), GL_UNSIGNED_INT, 0);
	}
}

void Renderer::SetupShaderUniforms(Material &material, Transform transform)
{
	material.Shader.Bind();
	material.Texture.Bind();

	glm::mat4 modelMatrix = Camera::GetModel(transform.position, transform.rotation);

	material.Shader.SetUniformMatrix4fv("uModel", modelMatrix);
	material.Shader.SetUniformMatrix4fv("uView", camera->GetView());
	material.Shader.SetUniformMatrix4fv("uProjection", camera->GetProjection());
	material.Shader.SetUniformMatrix4fv("uTexture", material.Texture.GetId());

	PointLight light = sceneLight.PointLights[0];
	material.Shader.SetUniform3f("uLightColor", light.Color);
	material.Shader.SetUniform3f("uLightPos", light.Position);
	material.Shader.SetUniform1f("uLightIntensity", light.Intensity);

}

void Renderer::DrawScene(Scene &scene)
{
	for (entt::entity entity : scene.GetEntitiesWithComponent<Model>())
	{
		Model& model = scene.GetComponent<Model>(entity);
		Transform& transform = scene.GetComponent<Transform>(entity);

		DrawModel(model, transform);
	}
}


void Renderer::BeginScene(std::shared_ptr<Camera> camera)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0);

	this->camera = camera;
}

void Renderer::EndScene()
{
	
}