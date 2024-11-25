#pragma once
#include <memory.h>
#include <string>
#include <glm/glm.hpp>
#include <vector>



enum ShaderType
{
	Vertex,
	Fragment
};

/*
	Shader abstraction
*/

class Shader
{
public:
	Shader() = default;
	Shader(const std::string& filename);
	Shader(const std::string& vertex, const std::string& fragment, const std::string& name = "");
	~Shader() = default;

	static std::string parseShader(const std::string& src, ShaderType type);
	static unsigned int compileShader(std::string src, const std::string& name, ShaderType type);
	static unsigned int linkShaders(unsigned int vertex, unsigned int fragment);

	// Integer uniforms
	void setUniform1i(const std::string& name, int val);
	void setUniform2i(const std::string& name, const glm::ivec2& value);
	void setUniform3i(const std::string& name, const glm::ivec3& value);
	void setUniform4i(const std::string& name, const glm::ivec4& value);

	// Unsigned integer uniforms
	void setUniform1ui(const std::string& name, unsigned int val);
	void setUniform2ui(const std::string& name, const glm::uvec2& value);
	void setUniform3ui(const std::string& name, const glm::uvec3& value);
	void setUniform4ui(const std::string& name, const glm::uvec4& value);

	// Float uniforms
	void setUniform1f(const std::string& name, float val);
	void setUniform2f(const std::string& name, const glm::vec2& value);
	void setUniform3f(const std::string& name, const glm::vec3& value);
	void setUniform4f(const std::string& name, const glm::vec4& value);

	// Matrix uniforms (2x2, 3x3, 4x4)
	void setUniformMatrix2fv(const std::string& name, const glm::mat2& matrix);
	void setUniformMatrix3fv(const std::string& name, const glm::mat3& matrix);
	void setUniformMatrix4fv(const std::string& name, const glm::mat4& matrix);

	// Other types (for example, vectors or arrays)
	void setUniform1iv(const std::string& name, int count, const int* values);
	void setUniform1fv(const std::string& name, int count, const float* values);
	void setUniform3fv(const std::string& name, int count, const glm::vec3* values);

	void Bind() const;
	void Unbind() const;


	inline std::string getName() { return this->name; }
	inline void setName(const std::string& name) { this->name = name; }
	inline unsigned int getId() { return id; }

private:
	std::string name;
	std::string vertex;
	std::string fragment;
	unsigned int id;
};

class Texture
{
private:
	unsigned int id;
	unsigned char* data;
	int width;
	int height;
	int nChannels;
	unsigned int textureId;

public:
	Texture() = default;
	Texture(std::string path);
	Texture(unsigned char* data, int width, int height) {}
	~Texture();

public:
	void bind(unsigned int tex = 0);
	void unbind();

	inline unsigned int getId() { return id; }
	inline unsigned int getTextureId() { return textureId; }
};

