#pragma once

#include "Resource.h"
#include <unordered_map>
#include <string>

class ResourceManager
{
public:
	std::unordered_map<std::string, Resource*> Resources;

	template<class T>
	T* Create(std::string name);
	template<class T>
	T* Get(std::string name);
	void Delete(std::string name);

};

template<class T>
inline T* ResourceManager::Create(std::string name)
{
	if (Resources[name] != nullptr)
		Delete(name);
	Resources[name] = new T;
	return T*;
}

template<class T>
inline T* ResourceManager::Get(std::string name)
{
	if (Resources[name] != nullptr)
		return T*;
	return nullptr;
}

void ResourceManager::Delete(std::string name)
{
	delete Resources[name];
	Resources.erase(name);
}

