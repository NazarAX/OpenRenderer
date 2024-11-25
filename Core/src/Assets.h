#pragma once
#include <unordered_map>
#include "Interface/Abstractions.h"
#include <string>
#include <iostream>



template <class T>
class AssetLibrary
{
private:
	std::unordered_map<std::string, T> assetMap;

public:
	AssetLibrary();
	~AssetLibrary();

	void Load(const T& asset, const std::string& name) 
	{
		assetMap[name] = asset;
	}

	T Get(const std::string& name)
	{
		return assetMap[name];
	}
};
