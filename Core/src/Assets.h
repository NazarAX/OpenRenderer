#pragma once
#include <map>
#include "Rendering/Abstractions.h"
#include <iostream>

namespace Assets 
{
	static std::map<std::string, Shader> shaders;
	static std::map<std::string, Texture> textures;

	static void addShader(const std::string& name, const Shader& shader) {
		shaders[name] = shader;
	}
	
	static void addTexture(const std::string& name, const Texture& texture) 
	{
		textures[name] = texture;
	}

	static Shader getShader(const std::string& name) 
	{
		auto it = shaders.find(name);

		if (it != shaders.end())
			return it->second;

		std::cerr << "Error: Shader " << name << " not found" << std::endl;
	}

	static Texture getTexture(const std::string& name)
	{
		auto it = textures.find(name);

		if (it != textures.end())
			return it->second;


		std::cerr << "Error: Texture " << name << " not found" << std::endl;
	}

}