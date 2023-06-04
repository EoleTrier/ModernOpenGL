#pragma once
#include "Core/Maths/Matrix4x4.h"

class Transform
{
public:
    Transform* Parent;
    std::vector<Transform*> Childs;
	Matrix4x4 GlobalModel;
    Vector3 Position;
    Vector3 Rotation;
    Vector3 Scaling;

    void updateSelfAndChild();
   
private:
	Matrix4x4 LocalModel;
};