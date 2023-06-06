#pragma once

#include "Resource.h"
#include <unordered_map>
#include <string>

class ResourceManager
{
public:

	std::unordered_map<std::string, Resource*> resources;

	template<class T>
	T* Create(std::string name);
	template<class T>
	T* Get(std::string name);
	void Delete(std::string name);
};

template<class T>
inline T* ResourceManager::Create(std::string name)
{
	if (resources[name] != nullptr)
		Delete(name);
	T* resource = new T;
	resources[name] = resource;
	return resource;
}

template<class T>
inline T* ResourceManager::Get(std::string name)
{
	return dynamic_cast<T*>(resources[name]);
}

inline void ResourceManager::Delete(std::string name)
{
	delete resources[name];
	resources.erase(name);
}


