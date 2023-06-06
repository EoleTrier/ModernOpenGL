#pragma once
#include <filesystem>
#include "Ressources/Resource.h"

class Texture : public Resource
{
public :
	Texture();
	unsigned int id;

	void Load(const char* filename);
};