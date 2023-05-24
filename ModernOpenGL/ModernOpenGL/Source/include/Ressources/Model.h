#pragma once
#include <vector>

#include "Resource.h"
#include "Core/Maths/Vector2.h"
#include "Core/Maths/Vector3.h"


struct Vertex
{
	Vector3 Position;
	Vector3 Normal;
	Vector2 TextureUV;
};

class Model : Resource
{
public:
	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;
    void Load(const char* modelPath);
};

