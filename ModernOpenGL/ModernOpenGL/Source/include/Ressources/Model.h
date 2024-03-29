#pragma once
#include <vector>

#include "Resource.h"
#include "Core/Maths/Vector2.h"
#include "Core/Maths/Vector3.h"
#include "Ressources/Shader.h"
#include "LowRenderer/Camera.h"
#include "LowRenderer/Mesh.h"
#include "Core/Object.h"
struct Vertex
{
	Vector3 Position;
	Vector3 Normal;
	Vector2 TextureUV;
};

class Model : public Resource
{
public:
	unsigned int VAO, VBO;
	Mesh* mesh;

	Model();
	~Model();
	std::vector<Vertex> vertices;
    void Load(const char* modelPath, const char* texturePath);
	
};

