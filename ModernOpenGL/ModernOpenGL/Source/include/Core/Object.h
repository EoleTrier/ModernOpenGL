#pragma once
#include "Physics/Transform.h"
#include "LowRenderer/Mesh.h"

class Object
{
public:
	Object();
	Object(const Transform& t);
	Mesh* mesh;
	Transform tranform;
};