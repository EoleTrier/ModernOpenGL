#pragma once
#include <filesystem>
#include "Ressources/Resource.h"

class Texture : public Resource
{
public :
	Texture(const char* filename);
	unsigned int ID;

};