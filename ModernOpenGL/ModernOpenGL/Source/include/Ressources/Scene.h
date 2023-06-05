#pragma once
#include "Resource.h"
#include "Physics/Transform.h"

class Scene : public Resource
{
public:
	Transform World;
	Scene(const Transform& t);
};