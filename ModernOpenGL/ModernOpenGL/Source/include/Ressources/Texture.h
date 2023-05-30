#pragma once
#include <filesystem>
#include "Ressources/Resource.h"

class Texture : public Resource
{
public :
	Texture();
	unsigned int ID;

	void Load(const char* filename);

};