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
	T* resource = new T;
	Resources[name] = resource;
	return resource;
}

template<class T>
inline T* ResourceManager::Get(std::string name)
{
	return dynamic_cast<T*>(Resources[name]);
}

inline void ResourceManager::Delete(std::string name)
{
	delete Resources[name];
	Resources.erase(name);
}


